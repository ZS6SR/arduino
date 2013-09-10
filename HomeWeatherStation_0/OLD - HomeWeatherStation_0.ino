/* Home Weather Station */
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,100,99);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

//#define ONE_WIRE_BUS 10       //Temp DS18B20 on pin 10
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);

int LM60_PinIn = A5;           //Temp sensor (LM60)
int PhotoCell_PinIn = 4;      //PhotoCell sensor

Adafruit_BMP085 bmp;

void setup()
{
  Serial.begin(9600);
  bmp.begin();
  sensors.begin();
  Serial.println("Initialize ... ");
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for Leonardo only
  //}
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  
}

void loop() 
{  
  // listen for incoming clients
  EthernetClient client = server.available();

  float temp0 = getTemp(getVolts(LM60_PinIn));
  delay(1);
  float temp1 = bmp.readTemperature();
  delay(1);
  int photocell_val = analogRead(PhotoCell_PinIn);
  delay(1);
  int pressure = bmp.readPressure() / 100;
  delay(1);
  
  Serial.println("LM60 ");
  Serial.println(temp0);
  Serial.println(" | BMP085 temp ");
  Serial.println(temp1);
  Serial.println(" | BMP085 Pressure ");
  Serial.println(pressure);
  
//  delay (1000);
  
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("~~");
//          sensors.requestTemperatures();
//          client.println("DS18B20 Temp: ");
//          client.println("sensors.getTempCByIndex(0)");
//          delay(1);
          //LM60 Temp Reading ========================================================

          client.print("LM60="); 
          client.print(temp0);
          client.print("~");
          delay(1);
          //BMP085 Temp Reading ========================================================
          client.print("BMP085=");
//          client.print(temp1);
          client.print("0");
          client.print("~");
          //PhotoCell Value ============================================================
          client.print("Light=");  
          client.print(photocell_val);
          client.print("~");
          //BMP085 Pressure Reading ========================================================
          client.print("hPa=");
//          client.print(bmp.readPressure() / 100);
          client.print("0");
          client.println("~~");
          client.println("</html>");
          delay(1);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }

  
  //Serial.println("Temperature - ");
  //Serial.println("=====================================================================================================");
  //Get Temprature from the DS18B20 Dallas One Wire Tmp Sensor
  //sensors.requestTemperatures();
  //Serial.print("DS18B20 Temp: ");  
  //Serial.print(sensors.getTempCByIndex(0));
  //delay(1);
  
  //Temp LM60 Value
  //float temp0 = getTemp(getVolts(LM60_PinIn));
  //Serial.print(" | LM60 Temp: "); 
  //Serial.print(temp0);
  //delay(1);
  
  //BMP085
  //Serial.print(" | BMP085 Temp: ");
  //Serial.println(bmp.readTemperature());
  //delay(1);

  //PhotoCell Value
  //Serial.print("LIGHT - ");  
  //int photocell_val = analogRead(PhotoCell_PinIn);
  //Serial.print(photocell_val);
  
  //Serial.print(" | BMP085 Pressure: ");
  //Serial.print(bmp.readPressure() / 100);
  //delay(1);
  //Serial.print(" hPa");
  //delay(1);
  
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  //Serial.print(" | BMP085 Altitude: ");
  //Serial.print(bmp.readAltitude());
  //delay(1);    
  //Serial.println(" m");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  //Serial.print(" | BMP085 Real altitude: ");
  //Serial.print(bmp.readAltitude(101500));
  //delay(1);    
  //Serial.print(" m");
  
  //Serial.println("=====================================================================================================");
  //Serial.println();
  //delay(5000);
}

float getVolts(int pinIn)
{
  int inputValue = 0;
  int bigT = 0, smallT = 0;

  for (int i = 0; i < 20; i++)
  {
    inputValue = analogRead(pinIn);
    bigT += inputValue;
    delay(1);
  }

  smallT = bigT / 20;

  float mV;
  mV = ((float)(smallT) * 1030 / 1024);
  mV = (mV - 0.5);
  mV = mV * 5;

  return mV;
}


float getTemp(float volts)
{
  float temp = (volts - 424) / 6.25;
  return temp;
}

