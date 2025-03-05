/*
 * firebase.c
 *
 *  Created on: Mar 1, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This file implements the function to upload sensor data to Firebase via GSM.
 */

#include "firebase.h"

// Instantiate the Firebase client with gsm_client, host, and port 80.
HttpClient firebaseClient = HttpClient(gsm_client, FIREBASE_HOST, 80);

/*
 * Initializes Firebase communication.
 */
void Firebase_Init(void)
{
    if (!gsm_isConnected()) {
        Serial.println("Firebase Init: GSM network not connected.");
        return;
    }
    if (!gsm_enableGPRS()) {
        Serial.println("Firebase Init: Failed to enable GPRS.");
        return;
    }
    Serial.println("Firebase is ready.");
}

/*
 * Sends sensor data to Firebase.
 */
bool Firebase_UploadData(float waterLevel, float temperature)
{
    if (!gsm_isConnected() || !gsm_enableGPRS()) {
        Serial.println("Cannot upload data: No network or GPRS.");
        return false;
    }

    // Construct JSON payload
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["water_level"] = waterLevel;
    jsonDoc["temperature"] = temperature;

    String payload;
    if (serializeJson(jsonDoc, payload) == 0) {
        Serial.println("Failed to serialize JSON.");
        return false;
    }

    // Construct Firebase API URL
    String url = String(FIREBASE_HOST) + "/data.json?auth=" + FIREBASE_API_KEY;

    for (int i = 0; i < 3; i++) { // Retry up to 3 times
        firebaseClient.beginRequest();
        firebaseClient.post(url);
        firebaseClient.sendHeader("Content-Type", "application/json");
        firebaseClient.sendHeader("Content-Length", payload.length());
        firebaseClient.beginBody();
        firebaseClient.print(payload);
        firebaseClient.endRequest();

        delay(200); // Allow response to be read

        int httpResponseCode = firebaseClient.responseStatusCode();
        Serial.print("Firebase Response Code: ");
        Serial.println(httpResponseCode);

        if (httpResponseCode == 200) {
            return true;
        }
        Serial.println("Retrying Firebase upload...");
    }

    return false;
}





