/*
 * espnow_receiver.c
 *
 *  Created on: Feb 18, 2025
 *      Author: Zaid Mostafa (Embedded legends member)
 *
 *  This file implements the ESP-NOW receiver functions.
 */

#include "Reciever.h"

/* Variable to hold received sensor data */
SensorData receivedData;
bool isRecieved = false;

/*
 * Callback function triggered when data is received.
 * - Copies received data into `receivedData` struct.
 * - Prints the received values to the Serial Monitor.
 * - Uploads the data to the Blynk dashboard.
 */
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&receivedData, incomingData, sizeof(receivedData)); // Copy received data
    Serial.printf("Received: Water Level = %.2f, Temperature = %.2f\n", receivedData.water_level, receivedData.temperature);
}

/*
 * Initializes ESP-NOW on the receiver ESP32.
 * - Connects to Wi-Fi and Blynk.
 * - Initializes ESP-NOW and registers a receive callback.
 */
void ESPNOW_Receiver_Init()
{
    WiFi.mode(WIFI_STA); // Set ESP32 to station mode

    // Connect to Wi-Fi and Blynk
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv); // Register receive callback
}



