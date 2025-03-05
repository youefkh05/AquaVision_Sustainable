/*
 * firebaseusingwifi.h
 *
 *  Created on: Feb 28, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This header declares functions for uploading sensor data
 *  (water level and temperature) to a Firebase Realtime Database via WiFi.
 *  It assumes that a WiFi connection is established before uploading data.
 */

#ifndef FIREBASEUSINGWIFI_H_
#define FIREBASEUSINGWIFI_H_

#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

/* Structure to hold sensor data */
typedef struct {
    float water_level;
    float temperature;
} SensorData;

/*
 * FirebaseWiFi_Init
 * Initializes the WiFi connection using the provided SSID and password.
 *
 * @param ssid     Your WiFi network name.
 * @param password Your WiFi network password.
 */
void FirebaseWiFi_Init(const char* ssid, const char* password);

/*
 * FirebaseWiFi_UploadData
 * Uploads sensor data to Firebase via WiFi.
 *
 * @param data: Pointer to a SensorData structure containing the sensor values.
 */
void FirebaseWiFi_UploadData(SensorData *data);

#endif /* FIREBASEUSINGWIFI_H_ */

