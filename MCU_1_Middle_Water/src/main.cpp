#include <Arduino.h>
#include "Water_Level/Water_Level.h"
#include "ESPNOW_Sender/Sender.h"

SensorData data;


void setup()
{
  Sensor_init(HCSR04);
  ESPNOW_Sender_Init();
  Serial.begin(9600);
}

void loop()
{
  data.water_level = getDepth_Average_cm(HCSR04); // Measure Water Level
  // Todo: Add measure temprature

  Serial.println(data.water_level);
  delay(500);

  ESPNOW_SendData(&data, sizeof(data));

  // ESP NOW Send Data
}


