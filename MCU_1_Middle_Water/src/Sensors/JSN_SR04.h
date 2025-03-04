#ifndef JSN_SR04_H
#define JSN_SR04_H

#include <Arduino.h>

// Pin definitions for communication (adjust as needed)
#define RX_PIN 16  // GPIO pin for receiving data from the sensor (use suitable pin)
#define TX_PIN 17  // GPIO pin for sending data to the sensor (use suitable pin)

// Initialize the communication with the sensor
void init_JSN_SR04();

// Read the distance data from the sensor
float get_distance_JSN_SR04();

#endif 
