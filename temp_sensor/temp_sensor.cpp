/*
 * Project  : DS18B20 Temperature Sensor with ESP32
 * Author   : Tesla
 * Date     : February 2025
 * 
 * Description:
 * This code reads the temperature from a DS18B20 sensor and displays it 
 * on the Serial Monitor. The serial output is only needed for testing 
 * and performance evaluation; it will not be required in the final project.
 */

// libararies (must be added ) 
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin where DS18B20 is connected
#define ONE_WIRE_BUS 0  // i use pin 0 , u can change it 

// Initialize the OneWire communication on the defined pin  
OneWire oneWire(ONE_WIRE_BUS);  

// Pass the OneWire reference to the DallasTemperature library  
// to manage communication with the DS18B20 sensor  
DallasTemperature sensors(&oneWire);

void setup() {
    Serial.begin(115200);
    sensors.begin();  // Initialize the sensor
}

void loop() {
    sensors.requestTemperatures();  // Request temperature from sensor
    float temperatureC = sensors.getTempCByIndex(0);  // Get temperature in Celsius

    // Print temperature
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println("°C");

    delay(1000);  // Wait 1 second before next reading
}