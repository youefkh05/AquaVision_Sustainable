/*************************************************************************
 * 
 *  Author:     Ameer Louly
 * 
 *  Date:       02/26/2025
 * 
*************************************************************************/

#include "Water_Level.h"
#include "../Sensors/HCSR04.h"

/***************************************************************************/

void Sensor_init(Sensor_Type sensor)
{
    switch(sensor)
    {
        case HCSR04:
            HCSR04_init();
            break;
        
        case Waterproof:
        //todo: Call Waterproof sensor init function
            break;

        case ToF:
        //todo: Call ToF Sensor init function
            break;
    }
}

/***************************************************************************************/

float32 getDepth_cm(Sensor_Type sensor)
{
    //todo: 5od el average bta3 5amas 2erayat
    float32 distance = 0;

    switch(sensor)
    {
        case HCSR04:
            distance = getDistanceinCM_HCSR04();
            break;
        
        case Waterproof:
        //todo: Call Waterproof sensor distance function and store in distance
            break;

        case ToF:
        //todo: Call ToF Sensor DIstance function and store in distance
            break;
    }

    return (CONTAINER_DEPTH_CM - distance);
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