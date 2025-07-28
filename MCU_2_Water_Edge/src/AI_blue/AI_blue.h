#ifndef AI_BLUE_H
#define AI_BLUE_H

#include <BluetoothSerial.h>

extern BluetoothSerial Bluetooth_serialESP;


/* Global Variables */
extern BluetoothSerial Bluetooth_serialESP;


#define BLUE_NAME "AquaVision_AI"
#define MAX_MESSAGES 10

/* Message Arrays */
/* Message Arrays */
extern const char* welcomeMessages[MAX_MESSAGES];
extern const char* waterMessages[MAX_MESSAGES];
extern const char* phMessages[MAX_MESSAGES];
extern const char* temperatureMessages[MAX_MESSAGES];

/* Bluetooth Initialization */
void BLUE_init(void);

/* Bluetooth Receive */
String BLUE_receive(void);

/* Send Random Message */
void sendRandomMessage(const char* messages[], int size);

void BLUE_processInput(void);

void printSensorReading(int value, int type);

#endif /* AI_BLUE_H */
