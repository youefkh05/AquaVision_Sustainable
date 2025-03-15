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
volatile bool isRecieved = false;

/*
 * Callback function triggered when data is received.
 * - Copies received data into `receivedData` struct.
 * - Prints the received values to the Serial Monitor.
 * - Uploads the data to the Blynk dashboard.
 */
volatile void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&receivedData, incomingData, sizeof(receivedData)); // Copy received data
    // Serial.printf("Received: Water Level = %.2f, Temperature = %.2f\n", receivedData.water_level_1, receivedData.temp);
    isRecieved = true;
}

/*
 * Initializes ESP-NOW on the receiver ESP32.
 * - Initializes ESP-NOW and registers a receive callback.
 */
void ESPNOW_Receiver_Init()
{
    WiFi.mode(WIFI_STA); // Set ESP32 to station mode

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed\n");
        return;
    }

    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv)); // Register receive callback
}



