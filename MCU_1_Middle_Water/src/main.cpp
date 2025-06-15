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
  DebugLED_init();
  Buzzer_init();
  Serial.begin(9600);
}

void loop()
{
  data.water_level = getDepth_Average_cm(CurrentSensor); // Measure Water Level
  data.temperature = Temp_getTempC();

  if(data.water_level < 10 || data.water_level > CONTAINER_DEPTH_CM)
  {
    Buzzer_on(); // Turn on buzzer if water level is out of range
  }
  else
  {
    Buzzer_off(); // Turn off buzzer if water level is within range
  }

  Serial.printf("\nMiddle Water Level:  %.02f\n",data.water_level);
  Serial.printf("Water Temprature:    %.02f\n",data.temperature);

  ESPNOW_SendData(&data, sizeof(data));
  DebugLED_on(Blue); // Turn on debug LED to indicate sending
  delay(200); // Delay of 500ms for ESP-NOW send interval
  DebugLED_off(Blue); // Turn off debug LED after sending
  delay(500); // Delay of 500ms for ESP-NOW send interval

  delay(1000); // Delay for 1 second
}


