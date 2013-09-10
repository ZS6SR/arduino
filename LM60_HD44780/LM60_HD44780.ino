#include <LiquidCrystal.h>

/* LiquidCrystal display with:
 LCD 4 (RS) to arduino pin 12
 LCD 5 (R/W) to ground (non-existent pin 14 okay?)
 LCD 6 (E) to arduino pin 11
 d4, d5, d6, d7 on arduino pins 7, 8, 9, 10
 */
LiquidCrystal lcd(12, 14, 11, 7, 6, 5, 4);

int backLight = 13;
int count = 0;

void setup() {
  delay(500);
  Serial.begin(9600);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
}

void loop()
{
  float temp0 = getTemp(getVolts(A2));
  count++;
  Serial.print(" === TESTING LCD - count >");
  Serial.print( count );
  Serial.println("< ===");
  delay(5000);
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("Temp: ");    // change this text to whatever you like. keep it clean.
  lcd.setCursor(6,0);           // set cursor to column 0, row 1
  lcd.print(temp0, 1);   // The int (1) tells the print to only use 1 palce after the decimal.
  lcd.setCursor(11,0);
  lcd.write(0xDF);
  lcd.setCursor(12,0);
  lcd.print("C");

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
