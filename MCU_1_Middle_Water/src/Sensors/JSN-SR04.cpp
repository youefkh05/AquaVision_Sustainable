#include "JSN_SR04.h"

// Create an instance of HardwareSerial for communication
HardwareSerial mySerial(1); // Use UART1, change to 0 if you're using UART0

// Initialize communication with the sensor
void init_JSN_SR04() {
  // Start serial communication for debugging
  Serial.begin(115200);  // Serial Monitor baud rate
  
  // Start UART1 communication at 9600 baud rate for the sensor
  mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  Serial.println("JSN-SR04 Initialized in UART Mode");
}

// Function to read the distance data from the sensor
float get_distance_JSN_SR04() {
  uint8_t data[9];  // Buffer to store the 9-byte data from the sensor
  float distance = -1.0; // Initialize the distance variable to an invalid value
  
  if (mySerial.available() >= 9) {  // Check if 9 bytes are available
    // Read the 9 bytes from the sensor
    for (int i = 0; i < 9; i++) {
      data[i] = mySerial.read();
    }

    // Check the first byte (start byte should be 0xFF)
    if (data[0] == 0xFF) {
      // Combine the low and high byte to form the distance as an integer
      int dist = data[1] | (data[2] << 8);  // Combining bytes

      // Convert the integer to a float
      distance = (float)dist;  // Distance is now in float format
    }
  }
  
  return distance;  // Return the measured distance
}
