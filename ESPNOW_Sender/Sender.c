/*
 * espnow_sender.c
 *
 *  Created on: Feb 16, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This file implements the ESP-NOW sender functions.
 */

#include "espnow_sender.h"

/* MAC address of the receiver ESP32
uint8_t receiverMAC[] = {0x##, 0x##, 0x##, 0x##, 0x##, 0x##};

/* Struct to hold sensor readings */
SensorData data;

/*
 * Callback function triggered after data is sent.
 * - Prints success or failure to Serial Monitor.
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

/*
 * Initializes ESP-NOW on the sender ESP32.
 * - Configures ESP32 to Station mode.
 * - Initializes ESP-NOW and registers a send callback.
 * - Adds the receiver as a communication peer.
 */
void ESPNOW_Sender_Init() {
    WiFi.mode(WIFI_STA); // Set ESP32 to station mode for ESP-NOW

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_register_send_cb(OnDataSent); // Register send status callback

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMAC, 6); // Set receiver MAC address
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo); // Add receiver as a peer
}

/*
 * Reads sensor values and sends them via ESP-NOW.
 * - Simulates water level and temperature readings.
 * - Sends the struct `SensorData` over ESP-NOW.
 */
void ESPNOW_SendData() {
    // Read water level sensor data
    data.water_level = /* Read water level sensor data here */;

    // Read temperature sensor data
    data.temperature = /* Read temperature sensor data here */;

    // Send the sensor data structure via ESP-NOW
    esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
}
