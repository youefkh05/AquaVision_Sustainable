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

// HardwareSerial for ESP32 (Using UART2 by default)
extern HardwareSerial SerialGSM;
extern TinyGsm modem;
extern TinyGsmClient gsm_client;

// APN for your GSM network (replace with your provider's APN)
#define APN "your_apn"

/* Initializes the GSM module */
void gsm_init(void);

/* Checks whether the SIM800L module is connected to the mobile network */
bool gsm_isConnected(void);

/* Enables GPRS for internet connectivity */
bool gsm_enableGPRS(void);

/* Disables GPRS to save power */
void gsm_disableGPRS(void);

#endif /* GSM_DRIVER_H_ */

