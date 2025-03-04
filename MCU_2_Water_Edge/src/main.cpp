#include <Arduino.h>
#include "Water_Level/Water_Level.h"

//todo: Create Global Struct Variable for data storing

void setup() {

  /*ESP NOW Init Start*/

  
  /*ESP NOW Init End*/

  Sensor_init(HCSR04);
  Serial.begin(9600);
}

void loop() {
  // Get Sensor Data

  // Recieve ESPNOW Data

  // Display Data on OLED

  // Send Data to web server
  Serial.println(getDepth_cm(HCSR04));
  delay(500);

}

//todo: Create ESP Now Recieve Data Call Back Function

