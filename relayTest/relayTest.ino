#include <LiquidCrystal.h>

/* LiquidCrystal display with:
 LCD 4 (RS) to arduino pin 12
 LCD 5 (R/W) to ground (non-existent pin 14 okay?)
 LCD 6 (E) to arduino pin 11
 d4, d5, d6, d7 on arduino pins 7, 8, 9, 10
 */
LiquidCrystal lcd(12, 14, 11, 7, 6, 5, 4);

int backLight = 13;
int relay = 9;
int buttonPin = 2;
int buttonState = LOW;
int count = 0;
int loopCount = 0;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  delay(500);
  pinMode(backLight, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
//  Serial.begin(9600);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  
  long tempTime = millis() - lastDebounceTime;
  if ( tempTime > debounceDelay ) {
    if( buttonState == HIGH ){
      digitalWrite(backLight, HIGH); //turn backlight on
      digitalWrite(relay, HIGH);
      lastDebounceTime = millis(); //set the current time
      loopCount = 0;
    }
  }

  if (loopCount > 3) {
    loopCount = 0;
    digitalWrite(backLight, LOW);
    digitalWrite(relay, LOW);
  }
  
  if (count > 500) {
    loopCount++;
//    Serial.print("About to get temp vals - count = ");
//    Serial.println(count);
//    Serial.print("loopCount = ");
//    Serial.println(loopCount);
    float temp0 = getTemp(getVolts(A2));
    lcd.setCursor(3,0);           // set cursor to column 0, row 0 (the first row)
    lcd.print("In :");    // change this text to whatever you like. keep it clean.
    lcd.setCursor(8,0);           // set cursor to column 0, row 1
    lcd.print(temp0, 1);   // The int (1) tells the print to only use 1 palce after the decimal.
    lcd.setCursor(12,0);
    lcd.write(0xDF);
//    lcd.setCursor(12,0);
//    lcd.print("C");
    
    float temp1 = getTemp(getVolts(A3));
    lcd.setCursor(3,1);           // set cursor to column 0, row 0 (the first row)
    lcd.print("Out:");    // change this text to whatever you like. keep it clean.
    lcd.setCursor(8,1);           // set cursor to column 0, row 1
    lcd.print(temp1, 1);   // The int (1) tells the print to only use 1 palce after the decimal.
    lcd.setCursor(12,1);
    lcd.write(0xDF);
//    lcd.setCursor(12,1);
//    lcd.print("C");
    count = 0;
  }
  
  delay (10);
  count++;

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
