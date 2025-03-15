/*
 * espnow_receiver.h
 *
 *  Created on: Feb 18, 2025
 *      Author: Zaid Mostafa (Embedded legends member)
 *
 *  This file defines the receiver ESP32's functions and data structures.
 */

#ifndef ESPNOW_RECEIVER_H_
#define ESPNOW_RECEIVER_H_

#include <esp_now.h>
#include <WiFi.h>

/* Define Blynk authentication token and Wi-Fi credentials */
#define BLYNK_AUTH          "Our_Blynk_Token"
#define WIFI_SSID           "oour_WiFi_SSID"
#define WIFI_PASS           "our_WiFi_Password"
#define ESPNOW_DEBUG_LED    2

/* Structure to hold received sensor data */
typedef struct
{
    float water_level_1;
    float temp;
} SensorData;

extern volatile bool isRecieved;
extern SensorData receivedData; // Global Object where Recieved data is stored

/* Function to initialize ESP-NOW communication */
void ESPNOW_Receiver_Init();

#endif /* ESPNOW_RECEIVER_H_ */

