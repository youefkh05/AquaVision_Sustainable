/*************************************************************************
 * 
 *  Author:     Ameer Louly
 * 
 *  Date:       02/26/2025
 * 
*************************************************************************/
#ifndef WATER_LEVEL_H
#define WATER_LEVEL_H

#include "../std_types.h"
#include <Arduino.h>

#define CONTAINER_DEPTH_CM     14

typedef enum
{
    HCSR04,
    Waterproof,
    ToF
} Sensor_Type;

void Sensor_init(Sensor_Type sensor);

float32 getDepth_cm(Sensor_Type sensor);
// Returns measured depth according to sensor type

#endif

