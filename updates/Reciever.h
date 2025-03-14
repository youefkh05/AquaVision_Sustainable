/*
 * espnow_receiver.h
 *
 *  Created on: Feb 18, 2025
 *      Author: Zaid Mostafa (Embedded legends member)
 *
 *  This file defines the receiver ESP32's functions and data structures.
 */
#ifndef RECIEVER_H
#define RECIEVER_H

#include "../common_includes.h"
#include <esp_now.h>
#include <WiFi.h>

/*
   SensorData structure definition.
   (This structure holds the sensor data received via ESP-NOW.)
*/
typedef struct {
    float water_level_1;
    float temp;
} SensorData;

// Extern declarations for global variables used in the Reciever module
extern SensorData receivedData;
extern volatile bool isReceived;

/*
   Function Prototypes
*/
void ESPNOW_Receiver_Init();
void Enable_WiFi();
void Enable_ESPNow();

#endif // RECIEVER_H

