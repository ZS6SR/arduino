#include <OneWire.h> 
#include <DallasTemperature.h> 
#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS); // on pin 10 DallasTemperature sensors(&oneWire);

DallasTemperature sensors(&oneWire);

void setup()
{  
  Serial.begin(9600);
  // Initialize sensors
  sensors.begin();
}

void loop()
{
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  Serial.print("Sensor #0: ");  
  Serial.println(sensors.getTempCByIndex(0));

  delay(100);  // wait a little time
}
