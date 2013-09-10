#include <LiquidCrystal.h>
#include "Keypad.h"

LiquidCrystal lcd(12, 14, 11, 10, 9, 8, 7);

// keypad type definition
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] =
 {{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
byte rowPins[ROWS] = {
  6, 5, 4, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  2, 1, 0}; // connect to the column pinouts of the keypad
int count=0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(2,0);
  lcd.print("Temp: ");
  Serial.begin(9600);
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
  
  Serial.print("Input Value: ") ; Serial.print(smallT);
  Serial.print(" | Voltage: ") ; Serial.print(mV);
  return mV;
  
}

float getTemp(float volts)
{
  //float temp = (volts - 0.5) / 0.01;
  float temp = (volts - 424) / 6.25;
  Serial.print(" | Temperature: "); Serial.print(temp); Serial.println(" 'C");
  return temp;
}

void loop() 
{  

  float temp0 = getTemp(getVolts(A0));
  Serial.print("Temp: "); Serial.println(temp0);
  Serial.println();
  lcd.setCursor(8, 0);
  lcd.print(temp0);
  lcd.setCursor(14,0);
  lcd.write(0xDF);
  lcd.setCursor(15,0);
  lcd.print("C");
  delay(20);
  lcd.setCursor(2, 2);
  lcd.print(millis()/1000);
  
  lcd.setCursor(8, 2);

  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    lcd.print(key);
//    count++;
//    if (count==17)
//    {
//      lcd.clear();
//      count=0;
//    }
  }
  
}


