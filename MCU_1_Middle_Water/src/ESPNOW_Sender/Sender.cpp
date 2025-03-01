/*
 * Sender.c
 *
 *  Created on: Feb 16, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This file implements the ESP-NOW sender functions.
 */

#include "Sender.h"

/* MAC address of the receiver ESP32*/
uint8_t receiverMAC[] = {0xCC, 0xDB, 0xA7, 0x9C, 0xED, 0x0C};

/*
 * Callback function triggered after data is sent.
 * - Prints success or failure to Serial Monitor.
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");

    // Debug LED Segnifying data sent
    digitalWrite(ESPNOW_DEBUG_LED, HIGH);
    delay(50);
    digitalWrite(ESPNOW_DEBUG_LED, LOW);
}

/*
 * Initializes ESP-NOW on the sender ESP32.
 * - Configures ESP32 to Station mode.
 * - Initializes ESP-NOW and registers a send callback.
 * - Adds the receiver as a communication peer.
 */
void ESPNOW_Sender_Init()
{
    WiFi.mode(WIFI_STA); // Set ESP32 to station mode for ESP-NOW

    while (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_register_send_cb(OnDataSent); // Register send status callback


    //todo: work on getting mac address (Awaiting Second ESP) 
    //todo: Work on finding a way to not make the MAC Address hard coded
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMAC, 6); // Set receiver MAC address
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo); // Add receiver as a peer

    pinMode(ESPNOW_DEBUG_LED, OUTPUT);
}

/*
 * Reads sensor values and sends them via ESP-NOW.
 * - Simulates water level and temperature readings.
 * - Sends the struct `SensorData` over ESP-NOW.
 */
void ESPNOW_SendData(SensorData *Data, uint8 size)
{
    // Send the sensor data structure via ESP-NOW
    esp_now_send(receiverMAC, (uint8_t *)Data, size);
}
