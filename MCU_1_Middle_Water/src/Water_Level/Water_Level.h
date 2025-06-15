/*************************************************************************
 * 
 *  Author:     Ameer Louly
 * 
 *  Date:       02/26/2025
 * 
*************************************************************************/
#ifndef WATER_LEVEL_H
#define WATER_LEVEL_H

#include "../common_includes.h"

#define WATER_LEVEL_DEBUG_LED_1     26
#define WATER_LEVEL_DEBUG_LED_2     32
#define WATER_LEVEL_BUZZER          13

#define CONTAINER_DEPTH_CM          25
#define AVERAGE_NUM                 5

typedef enum
{
    HCSR04,
    Waterproof,
    ToF
} Sensor_Type;

typedef enum
{
    Blue,
    Red
}   LedColor_t;

//todo: Add Structure data type to hold measured data

void Sensor_init(Sensor_Type sensor);

float32 getDepth_cm(Sensor_Type sensor);
// Returns measured depth according to sensor type

float32 getDepth_Average_cm(Sensor_Type sensor);
// Returns the average of the last 5 readings

void DebugLED_init();
void DebugLED_on(LedColor_t color);
void DebugLED_off(LedColor_t color);

void Buzzer_init();
void Buzzer_on();
void Buzzer_off();

//todo: Add temprature sensor functions

#endif

