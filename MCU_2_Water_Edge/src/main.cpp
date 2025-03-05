#include <Arduino.h>
#include "Water_Level/Water_Level.h"
#include "ESPNOW_Reciever/Reciever.h"

struct Data : public SensorData
{
  float32 water_level_2;
} AllData;
// Struct to store all data

//todo: Create Global Struct Variable for data storing
extern SensorData receivedData;

void setup() {

  ESPNOW_Receiver_Init();

  Sensor_init(HCSR04);
  Serial.begin(9600);
}

void loop() {
  // Get Sensor Data
  //AllData.water_level_2 = getDepth_Average_cm(HCSR04);

  Serial.println("Recieveing Data...");
  while(isRecieved == false) {}
  isRecieved = false;

  AllData.water_level_1 = receivedData.water_level_1;
  AllData.temp = receivedData.temp;
  // Recieve ESPNOW Data: Interrupt

  Serial.printf("Water Level 1: %.2f\n", AllData.water_level_1);

  // Display Data on OLED

  // Send Data to web server

}
