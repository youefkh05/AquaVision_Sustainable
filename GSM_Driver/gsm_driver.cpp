/*
 * gsm_driver.cpp
 *
 *  Created on: Mar 1, 2025
 *      Author: Ziad Mostafa (Embedded Legeneds member)
 *
 *  This file implements GSM management functions for the SIM800L module using TinyGSM.
 */

#include "gsm_driver.h"

// Using ESP32 HardwareSerial on UART2
HardwareSerial SerialGSM(2);
TinyGsm modem(SerialGSM);
TinyGsmClient gsm_client(modem);

/*
 * Initializes the SIM800L module and connects to the network.
 */
void gsm_init(void)
{
    SerialGSM.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial.println("Initializing GSM...");

    // Power on the SIM800L module
    modem.sendAT("+CFUN=1");
    delay(1000);

    if (!modem.restart()) {
        Serial.println("Failed to restart GSM module!");
        return;
    }

    Serial.println("Modem restarted. Checking network...");

    // Check if SIM card is inserted
    if (modem.getSimStatus() != 3) {
        Serial.println("SIM card not detected!");
        return;
    }

    // Connect to the GSM network
    if (!gsm_isConnected()) {
        Serial.println("Failed to connect to network.");
        return;
    }

    // Enable GPRS for HTTP requests
    if (!gsm_enableGPRS()) {
        Serial.println("Failed to enable GPRS.");
        return;
    }

    Serial.println("GSM module is ready.");
}

/*
 * Checks if the SIM800L is connected to a mobile network.
 */
bool gsm_isConnected(void)
{
    Serial.println("Checking network connection...");
    if (!modem.waitForNetwork(60000)) { // Wait up to 60 seconds
        Serial.println("Network unavailable!");
        return false;
    }
    Serial.println("Network connected.");
    return true;
}

/*
 * Enables GPRS for data transfer.
 */
bool gsm_enableGPRS(void)
{
    Serial.println("Enabling GPRS...");
    
    if (modem.isGprsConnected()) {
        Serial.println("GPRS already enabled.");
        return true;
    }

    // Try to connect with APN (Modify APN credentials if required)
    for (int i = 0; i < 3; i++) {
        if (modem.gprsConnect(APN, "", "")) {
            Serial.println("GPRS connected.");
            return true;
        }
        Serial.println("Retrying GPRS connection...");
        delay(3000);
    }

    Serial.println("GPRS connection failed!");
    return false;
}

/*
 * Disables GPRS to save power.
 */
void gsm_disableGPRS(void)
{
    Serial.println("Disabling GPRS...");
    modem.gprsDisconnect();
    Serial.println("GPRS disconnected.");
}
