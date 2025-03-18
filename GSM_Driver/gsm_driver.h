/*
 * gsm_driver.h
 *
 *  Created on: Mar 1, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This header provides declarations for GSM management using the SIM800L module.
 *  It uses the TinyGsm library to handle modem initialization, network connection,
 *  and HTTP communications.
 */

#ifndef GSM_DRIVER_H_
#define GSM_DRIVER_H_

#include <TinyGsmClient.h>
#include <Arduino.h>

// Define SIM800L module for TinyGSM
#define TINY_GSM_MODEM_SIM800

// ESP32 UART2 Pins for SIM800L (Make sure these match your wiring)
#define RXD2 16  // GPIO16 (ESP32 RX2)
#define TXD2 17  // GPIO17 (ESP32 TX2)

// Declare GSM objects globally
extern HardwareSerial SerialGSM;
extern TinyGsm modem;
extern TinyGsmClient gsm_client;

// APN for your GSM network (Replace "your_apn" with your actual APN)
#define APN "your_apn"

/* Initializes the GSM module */
void gsm_init(void);

/* Checks if the SIM800L module is connected to the mobile network */
bool gsm_isConnected(void);

/* Enables GPRS for internet connectivity */
bool gsm_enableGPRS(void);

/* Disables GPRS to save power */
void gsm_disableGPRS(void);

#endif /* GSM_DRIVER_H_ */
