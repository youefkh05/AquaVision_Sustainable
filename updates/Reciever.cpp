/*
 * espnow_receiver.h
 *
 *  Created on: Feb 18, 2025
 *      Author: Zaid Mostafa (Embedded legends member)
 *
 *  This file defines the receiver ESP32's functions and data structures.
 */
#include "Reciever.h"
#include "esp_wifi.h"
#include <WiFi.h>
#include <esp_now.h>

// Global variable definitions
SensorData receivedData;
volatile bool isReceived = false;  // >>> HIGHLIGHT: Flag set to true when data is received via ESP-NOW

/*
 * Callback function triggered when data is received via ESP-NOW.
 * Copies incoming data into the global "receivedData" structure.
 */
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&receivedData, incomingData, sizeof(receivedData));
    Serial.printf("Received: Water Level = %.2f, Temperature = %.2f\n", receivedData.water_level_1, receivedData.temp);
    isReceived = true;  // >>> HIGHLIGHT: Set flag to indicate data has been received
}

/*
 * Initializes ESP-NOW on the receiver ESP32.
 * >>> HIGHLIGHT: Sets WiFi to STA mode and disconnects from any router
 * to allow ESP-NOW to function without interference.
 */
void ESPNOW_Receiver_Init()
{
    WiFi.mode(WIFI_STA);              // >>> HIGHLIGHT: Use STA mode for ESP-NOW
    WiFi.disconnect(true);            // >>> HIGHLIGHT: Disconnect WiFi from router to avoid conflicts

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("ESP-NOW initialized in STA mode (WiFi disconnected).");  // >>> HIGHLIGHT: Confirmation message
}

/*
 * Enables WiFi for Firebase communication.
 * >>> HIGHLIGHT: Connects to the WiFi network using STA mode.
 */
void Enable_WiFi()
{
    WiFi.mode(WIFI_STA);              // >>> HIGHLIGHT: Ensure STA mode remains active
    WiFi.begin("WIFI_SSID", "WIFI_PASSWORD"); // >>> HIGHLIGHT: Replace with  actual credentials

    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi for Firebase...");
        delay(1000);
    }
    Serial.println("WiFi Connected for Firebase!");  // >>> HIGHLIGHT: WiFi connection established
}

/*
 * Switches back to ESP-NOW mode after Firebase upload.
 * >>> HIGHLIGHT: Disconnects from the WiFi network to resume ESP-NOW operation.
 */
void Enable_ESPNow()
{
    WiFi.disconnect(true);  // >>> HIGHLIGHT: Disconnect from WiFi to prevent interference with ESP-NOW
    WiFi.mode(WIFI_STA);      // >>> HIGHLIGHT: Maintain STA mode for ESP-NOW
    Serial.println("Switched back to ESP-NOW mode (WiFi disconnected).");  // >>> HIGHLIGHT: Confirmation message
}





