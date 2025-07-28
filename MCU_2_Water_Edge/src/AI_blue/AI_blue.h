#include "../common_includes.h"
#include <BluetoothSerial.h>

/* Global Variables */
BluetoothSerial Bluetooth_serialESP;

#define BLUE_NAME "AquaVision_AI"
#define MAX_MESSAGES 10

/* Message Arrays */
const char* welcomeMessages[MAX_MESSAGES] = {
  "Hello, fish farmer!",
  "Welcome to AquaVision!",
  "Nice to see you!",
  "System ready and watching your tank!",
  "Hey there! AquaVision at your service.",
  "Good day! Monitoring in progress.",
  "Welcome aboard!",
  "Ready to optimize your aquaculture.",
  "Sensors are all set.",
  "Data flows, AquaVision knows!"
};

const char* waterMessages[MAX_MESSAGES] = {
  "Water levels are optimal!",
  "The water is calm and clear.",
  "All systems show good water status.",
  "Tank water is within safe range.",
  "Water conditions are being monitored.",
  "H2O is healthy today!",
  "Water quality checks out.",
  "Looks like the water is doing fine.",
  "No water alerts at the moment.",
  "Fish are swimming happy!"
};

const char* phMessages[MAX_MESSAGES] = {
  "pH is balanced and healthy.",
  "pH levels are looking good!",
  "Current pH: within ideal range.",
  "pH sensors report stable readings.",
  "No pH issues detected.",
  "Aquatic chemistry looks great.",
  "All pH systems are green.",
  "Fish approve of today's pH!",
  "pH is within the safe zone.",
  "Perfect acidity levels right now!"
};

