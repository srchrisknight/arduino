#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
float CurrentTemp = 0;

void setup(void) 
{
 Serial.begin(9600); 
 sensors.begin(); 
} 
void loop(void) 
{ 
 sensors.requestTemperatures();
 CurrentTemp = sensors.getTempCByIndex(0) * 1.8 + 32;
 Serial.println(CurrentTemp);
 delay(1000); 
} 
