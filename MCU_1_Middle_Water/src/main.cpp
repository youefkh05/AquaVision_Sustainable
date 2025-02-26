#include <Arduino.h>
#include "Water_Level/Water_Level.h"


void setup() {

  /*ESP NOW Init Start*/


  /*ESP NOW Init End*/

  Sensor_init(HCSR04);
  Serial.begin(9600);
}

void loop() {
  Serial.println(getDepth_cm(HCSR04));
  delay(500);

  // ESP NOW Send Data
}

//todo: Create ESP Now Send Data Call Back Function

