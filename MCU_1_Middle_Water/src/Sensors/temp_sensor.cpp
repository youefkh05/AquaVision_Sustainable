#include "temp_sensor.h"

OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);

void Temp_init(void)
{
    sensors.begin();
}

float32 Temp_getTempC(void)
{
    sensors.requestTemperatures();  // Request temperature from sensor
    float32 temperatureC = sensors.getTempCByIndex(0);  // Get temperature in Celsius

    return temperatureC;
}