#include <Arduino.h>
#include "Water_Level/Water_Level.h"
#include "ESPNOW_Sender/Sender.h"
#include "Sensors/temp_sensor.h"

SensorData data;
Sensor_Type CurrentSensor = HCSR04;

void setup()
{
  Sensor_init(CurrentSensor);
  ESPNOW_Sender_Init();
  Temp_init();
  Serial.begin(9600);
}

void loop()
{
  data.water_level = getDepth_Average_cm(CurrentSensor); // Measure Water Level
  data.temperature = Temp_getTempC();

  Serial.printf("\nMiddle Water Level:  %.02f\n",data.water_level);
  Serial.printf("Water Temprature:    %.02f\n",data.temperature);

  ESPNOW_SendData(&data, sizeof(data));
  delay(700); // Delay of 500ms for ESP-NOW send interval
  // ESP NOW Send Data

  delay(1000); // Delay for 1 second
}


