/*
 * firebaseusingwifi.cpp
 *
 *  Created on: Feb 28, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This file implements functions to upload sensor data to Firebase using WiFi.
 *  It uses the ESP32's WiFi and HTTPClient libraries along with ArduinoJson.
 */

#include "firebaseusingwifi.h"

// Firebase credentials (replace these with your actual project details)
#define FIREBASE_API_KEY       "firebase_api_key"
#define FIREBASE_DATABASE_URL  "firebase_url"

void FirebaseWiFi_Init(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ");
    Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void FirebaseWiFi_UploadData(SensorData *data) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Cannot upload data: WiFi not connected.");
        return;
    }

    HTTPClient http;
    String url = String(FIREBASE_DATABASE_URL) + ".json?auth=" + String(FIREBASE_API_KEY);
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> jsonDoc;
    jsonDoc["water_level"] = data->water_level;
    jsonDoc["temperature"] = data->temperature;

    String payload;
    serializeJson(jsonDoc, payload);

    int httpResponseCode = http.POST(payload);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
}


