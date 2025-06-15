/*************************************************************************
 * 
 *  Author:     Ameer Louly
 * 
 *  Date:       02/26/2025
 * 
*************************************************************************/

#include "Water_Level.h"
#include "../Sensors/HCSR04.h"
#include "../Sensors/VL53L0X.h"
#include "../Sensors/JSN_SR04.h"
/***************************************************************************/

void Sensor_init(Sensor_Type sensor)
{
    switch(sensor)
    {
        case HCSR04:
            HCSR04_init();
            break;
        
        case Waterproof:
            init_JSN_SR04();
            break;

        case ToF:
            VL53L0X_init();
            break;
    }
}

/***************************************************************************************/

float32 getDepth_cm(Sensor_Type sensor)
{
    float32 distance = 0;

    switch(sensor)
    {
        case HCSR04:
            distance = getDistanceinCM_HCSR04();
            break;
        
        case Waterproof:
            distance = get_distance_JSN_SR04();
            break;

        case ToF:
            distance = getDistanceinCM_VL53L0X();
            break;
    }

    // return (CONTAINER_DEPTH_CM - distance);
    return distance;
}

/****************************************************************************************/

float32 getDepth_Average_cm(Sensor_Type sensor)
{
    float32 sum = 0;
    for(uint8 i = 0; i < AVERAGE_NUM; i++)
    {
        sum += getDepth_cm(sensor);
    }

    return (sum / AVERAGE_NUM);
}

void DebugLED_init()
{
    pinMode(WATER_LEVEL_DEBUG_LED_1, OUTPUT);
    pinMode(WATER_LEVEL_DEBUG_LED_2, OUTPUT);
}


void DebugLED_on(LedColor_t color)
{
    switch(color)
    {
        case Blue:
            digitalWrite(WATER_LEVEL_DEBUG_LED_1, HIGH);
            break;

        case Red:
            digitalWrite(WATER_LEVEL_DEBUG_LED_2, HIGH);
            break;
    }
}
void DebugLED_off(LedColor_t color)
{
    switch(color)
    {
        case Blue:
            digitalWrite(WATER_LEVEL_DEBUG_LED_1, LOW);
            break;

        case Red:
            digitalWrite(WATER_LEVEL_DEBUG_LED_2, LOW);
            break;
    }
}

void Buzzer_init()
{
    pinMode(WATER_LEVEL_BUZZER, OUTPUT);
    Buzzer_off(); // Ensure buzzer is off initially
}

void Buzzer_on()
{
    digitalWrite(WATER_LEVEL_BUZZER, HIGH);
}

void Buzzer_off()
{
    digitalWrite(WATER_LEVEL_BUZZER, LOW);
}