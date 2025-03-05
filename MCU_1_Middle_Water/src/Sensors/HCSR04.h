/*************************************************************************
 * 
 *  Author:     Ameer Louly
 * 
 *  Date:       02/26/2025
 * 
*************************************************************************/

#ifndef HCSR04_H
#define HCSR04_H

#include "../common_includes.h"

#define TRIG_PIN 16
#define ECHO_PIN 4

void HCSR04_init(void);
// Intializes the Sensors

void sendTrig(void);
// Sends Appropriate trigger to Ultrasonic HCSR04

float32 getDistanceinCM_HCSR04(void);
// Calculates the returns the distance measured by the sensor

#endif