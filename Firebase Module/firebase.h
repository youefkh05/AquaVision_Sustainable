/*
 * firebase.h
 *
 *  Created on: Mar 1, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This header declares functions for uploading sensor data
 *  (water level and temperature) to Firebase using GSM.
 */

#ifndef FIREBASE_H_
#define FIREBASE_H_

#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "gsm_driver.h"  // Provides gsm_client, gsm_isConnected(), and gsm_enableGPRS()

// Firebase details (update with your actual Firebase project details)
#define FIREBASE_API_KEY "your_firebase_api_key"
#define FIREBASE_HOST "your-firebase-url.firebaseio.com"  // Exclude "https://"; using HTTP on port 80

// Firebase client (using GSM)
extern HttpClient firebaseClient;

/* Initializes Firebase communication */
void Firebase_Init(void);

/* Uploads sensor data to Firebase */
bool Firebase_UploadData(float waterLevel, float temperature);

#endif /* FIREBASE_H_ */

