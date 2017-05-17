#include <dht.h>

#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include <OneWire.h>


/* LiquidCrystal display with:
  LCD 4 (RS) to arduino pin 12
  LCD 5 (R/W) to ground (non-existent pin 14 okay?)
  LCD 6 (E) to arduino pin 11
  LCD D4 pin to digital pin 5
  LCD D5 pin to digital pin 4
  LCD D6 pin to digital pin 3
  LCD D7 pin to digital pin 2
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int backLight = 13;
int count = 0;

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 8
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

#define DHT11_PIN 7
dht DHT;

#define RELAY1 A4

void setup() {
  delay(500);
  Serial.begin(9600);
  pinMode(backLight, OUTPUT);
  pinMode(RELAY1, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16, 2);             // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
  sensors.begin();
}

void loop()
{

  // Send the command to get temperatures
  sensors.requestTemperatures();  
  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("DHT Temp = ");
  Serial.println(DHT.temperature);
  Serial.print("DHT Humidity = ");
  Serial.println(DHT.humidity);
  
  count++;
  
  Serial.print(" === TESTING LCD - count >");
  Serial.print( count );
  Serial.println("< ===");
  
  if (sensors.getTempCByIndex(0) < 15) {
    lcd.clear();
    lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
    lcd.print((char)223);        //This is the degrees symbol
    lcd.print("C: ");
    lcd.print( (sensors.getTempCByIndex(0) + DHT.temperature )/2 );
    lcd.setCursor(0, 1);
    lcd.print("RH: ");
    lcd.print(DHT.humidity);
    digitalWrite(RELAY1,1);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
    lcd.print((char)223);
    lcd.print("C: ");
    lcd.print( (sensors.getTempCByIndex(0) + DHT.temperature )/2 );
    lcd.setCursor(0, 1);
    lcd.print("RH: ");
    lcd.print(DHT.humidity);
    digitalWrite(RELAY1,0);
  }
  delay(1000);

}
