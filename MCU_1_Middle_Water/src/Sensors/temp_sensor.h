#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

// Pin where DS18B20 is connected
#define ONE_WIRE_BUS 27  // i use pin 0 , u can change it

#include "../std_types.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

void Temp_init(void);
float32 Temp_getTempC(void);

#endif