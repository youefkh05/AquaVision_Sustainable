/*
 * espnow_sender.h
 *
 *  Created on: Feb 16, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This file defines the sender ESP32's functions and data structures.
 */

#ifndef ESPNOW_SENDER_H_
#define ESPNOW_SENDER_H_

#include <esp_now.h>
#include <WiFi.h>
#include "../common_includes.h"

#define ESPNOW_DEBUG_LED    2

/* Structure to hold sensor data */
typedef struct {
    float32 water_level;  // Water level sensor reading
    float32 temperature;  // Temperature sensor reading
} SensorData;

/* Function to initialize ESP-NOW communication */
void ESPNOW_Sender_Init();

/* Function to send sensor data */
void ESPNOW_SendData(SensorData *Data, uint8 size);

#endif /* ESPNOW_SENDER_H_ */
