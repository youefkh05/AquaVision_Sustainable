#include <Arduino.h>
#include "Water_Level/Water_Level.h"


void setup() {
  Sensor_init(HCSR04);
  Serial.begin(9600);
}

void loop() {
  Serial.println(getDepth_cm(HCSR04));
  delay(500);
}

