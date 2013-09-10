#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 8     // what pin we're connected to (DHT22)
#define DHTTYPE DHT22   // DHT 22  (AM2302)

/*************************************************** 
 * This is an example for the BMP085 Barometric Pressure & Temp Sensor
 * 
 * Designed specifically to work with the Adafruit BMP085 Breakout 
 * ----> https://www.adafruit.com/products/391
 * 
 * These displays use I2C to communicate, 2 pins are required to  
 * interface
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 * BSD license, all text above must be included in any redistribution
 ****************************************************/

// ============= BMP085 ============= 
// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

Adafruit_BMP085 bmp;

// ============= DHT22 ============= 
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

/* LiquidCrystal display with:
 LCD 4 (RS) to arduino pin 12
 LCD 5 (R/W) to ground (non-existent pin 14 okay?)
 LCD 6 (E) to arduino pin 11
 d4, d5, d6, d7 on arduino pins 7, 8, 9, 10
 */
LiquidCrystal lcd(12, 14, 11, 7, 6, 5, 4);

void setup() {
  Serial.begin(9600);
  // position cursor on line x=4,y=3
  lcd.begin(16, 2);
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    int count = 0;
    while (1) { 
      Serial.println("  ** Error "); 
      count++; 
    }
  }

  dht.begin();
}

void loop() {
  Serial.println("===========================================================");
  float temp0 = getTemp(getVolts(A2));
  Serial.print("LM60 Temperature: "); 
  Serial.print(temp0);
  Serial.println(" *C");

  float bt = bmp.readTemperature();
  float bp = bmp.readPressure();

  if (isnan(bt) || isnan(bp)) {
    Serial.println("Failed to read from DHT");
  } 
  else {
    Serial.print("BMP085 Temperature = ");
    Serial.print(bt);
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bp);
    Serial.println(" Pa");
  }
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  //  Serial.print("Altitude = ");
  //  Serial.print(bmp.readAltitude());
  //  Serial.println(" meters");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  //    Serial.print("Real altitude = ");
  //    Serial.print(bmp.readAltitude(101500));
  //    Serial.println(" meters");

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } 
  else {
    Serial.print("DHT22 Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("DHT22 Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }

  Serial.println();
  Serial.print("**** Average Temp: "); 
  float totalTemp = temp0 + bt + t;
  float avgTemp = totalTemp / 3;
  Serial.print(avgTemp);
  Serial.println(" ****");
  
  lcd.setCursor(0, 0);
  lcd.print("Tmp: ");
  lcd.setCursor(5, 0);
  lcd.print(avgTemp);
  lcd.setCursor(11, 0);
  lcd.write(0xDF);
  lcd.setCursor(12,0);
  lcd.print("C");
  
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.setCursor(5,1);
  lcd.print(h);
  lcd.setCursor(11, 1);
  lcd.write("%");
  
  delay(15000);
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
  //  volts = (((float)smallT / 1024) * 5000);

  Serial.print("Input Value: ") ; 
  Serial.print(smallT);
  Serial.print(" | Voltage: ") ; 
  Serial.print(mV);
  return mV;

}

float getTemp(float volts)
{
  //float temp = (volts - 0.5) / 0.01;
  float temp = (volts - 424) / 6.25;
  Serial.print(" | Temperature: "); 
  Serial.print(temp); 
  Serial.println(" 'C");
  return temp;
}





