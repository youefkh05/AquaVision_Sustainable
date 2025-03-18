#include <Arduino.h>
#include "Water_Level/Water_Level.h"
#include "ESPNOW_Reciever/Reciever.h"
#include "OLED/oled.h"
#include "Firebase_Sender.h"
#include "esp_wifi.h"
#include <WiFi.h>
#include "U8g2lib.h"  // OLED library

// OLED Display Initialization
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

/* Structure to store combined sensor data */
struct Data : public SensorData {
  float32 water_level_2;
} AllData;

/* External variable from Reciever.cpp */
extern SensorData receivedData;

/* Menu Variables */
const unsigned char* menu_icons[3] = {
  menu_icon_waterdrop,
  menu_icon_battery,
  menu_icon_temp
};

const int n_items = 3;
char items[n_items][20] = {
  {"Water level"},
  {"Battery level"},
  {"Temperature"}
};

int previous;
int selected = 0;
int next;
int current_screen = 0;

/* Temperature measurements */
int temp_progress = 0;
float temp = 24;
char temp_buffer[10];

/* Water level measurements */
int progress = 0;
float depth_1 = 0;
char buffer[10];

void setup() {
  /* Initializations */
  Sensor_init(HCSR04);
  OLED_init();
  Setup_Firebase();           // 🔹 **Initialize Firebase**
  ESPNOW_Receiver_Init();     // 🔹 **Initialize ESP-NOW reception (WiFi STA mode)**
  Serial.begin(9600);

  /* OLED Configuration */
  u8g2.setColorIndex(1);   // White color
  u8g2.setBitmapMode(1);
  u8g2.begin();
}

void loop() {
  Serial.println("Waiting for ESP-NOW data...");
  while (!isReceived) {}  // 🔹 **Wait for ESP-NOW data before switching to WiFi**
  isReceived = false;

  /* Store received data from ESP-NOW */
  AllData.water_level_1 = receivedData.water_level_1;
  AllData.temp = receivedData.temp;
  depth_1 = AllData.water_level_1;

  Serial.printf("Received: Water Level 1 = %.2f, Temperature = %.2f\n", AllData.water_level_1, AllData.temp);

  /* Menu Navigation - Button Control (Original Logic) */
  if (current_screen == 0) {
    // Up Button
    if (digitalRead(OLED_BUTTON_UP_PIN) == LOW) {
      delay(200);
      selected = selected - 1;
      if (selected < 0) {
        selected = n_items - 1;
      }
    }

    // Down Button
    if (digitalRead(OLED_BUTTON_DOWN_PIN) == LOW) {
      delay(200);
      selected = selected + 1;
      if (selected == n_items) {
        selected = 0;
      }
    }

    previous = selected - 1;
    if (previous < 0) {
      previous = n_items - 1;
    }
    next = selected + 1;
    if (next >= n_items) {
      next = 0;
    }
  }

  // Select Button toggles between menu and detailed display
  if (digitalRead(OLED_BUTTON_SELECT_PIN) == LOW) {
    delay(200);
    current_screen = !current_screen;
  }

  /* OLED Display Update */
  u8g2.firstPage();
  do {
    if (current_screen == 0) {
      // Menu display
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(26, 15, items[0]);
      u8g2.drawXBMP(4, 2, 16, 16, menu_icons[0]);

      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(26, 37, items[1]);
      u8g2.drawXBMP(4, 24, 16, 16, menu_icons[1]);

      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(26, 59, items[2]);
      u8g2.drawXBMP(4, 46, 16, 16, menu_icons[2]);

      if (selected == 0)
        u8g2.drawXBMP(0, 0, 128, 20, menu_sel_outline);
      else if (selected == 1)
        u8g2.drawXBMP(0, 22, 128, 20, menu_sel_outline);
      else if (selected == 2)
        u8g2.drawXBMP(0, 44, 128, 20, menu_sel_outline);

      u8g2.drawXBMP(120, 0, 8, 64, menu_scrollbar_bckg);
      u8g2.drawBox(125, 64 / n_items * selected + 6, 3, 8);
    } else {
      // Detailed display based on selected menu item
      u8g2.setFont(u8g2_font_helvB08_tr);
      if (selected == 0) { // Water Level detail
        dtostrf(depth_1, 6, 2, buffer);
        u8g2.drawXBMP(0, 0, 128, 64, waterlevel_measurement);
        u8g2.drawStr(25, 55, buffer);
        u8g2.drawBox(2, 16, progress, 6);
      } else if (selected == 2) { // Temperature detail
        dtostrf(temp, 6, 2, temp_buffer);
        u8g2.drawXBMP(0, 0, 128, 64, temp_measurement);
        u8g2.drawStr(25, 55, temp_buffer);
        u8g2.drawBox(2, 16, temp_progress, 6);
      }
    }
  } while (u8g2.nextPage());

  /* Update Progress Bars */
  if ((temp_progress < 124) && (depth_1 < 40))
    temp_progress = (depth_1 * 124) / 40;
  else
    temp_progress = 0;

  depth_1 += 0.05;
  if (depth_1 > 20)
    depth_1 = 5.5;

  if (progress < 124 && depth_1 < 20)
    progress = (depth_1 * 124) / 20;
  else
    progress = 0;

  /* 🔹 Enable WiFi and send data to Firebase */
  Enable_WiFi();

  Send_Firebase_Data(AllData.water_level_1, AllData.temp,32,32);

  /* 🔹 Switch back to ESP-NOW mode (Disconnect WiFi from router) */
  Enable_ESPNow();
}
