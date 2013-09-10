/*
 ADXL3xx
 
 Reads an Analog Devices ADXL3xx accelerometer and communicates the
 acceleration to the computer.  The pins used are designed to be easily
 compatible with the breakout boards from Sparkfun, available from:
 http://www.sparkfun.com/commerce/categories.php?c=80

 http://www.arduino.cc/en/Tutorial/ADXL3xx

 The circuit:
 analog 0: accelerometer self test
 analog 1: z-axis
 analog 2: y-axis
 analog 3: x-axis
 analog 4: ground
 analog 5: vcc
 
 created 2 Jul 2008
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe 
 
 This example code is in the public domain.

*/

// these constants describe the pins. They won't change:
//const int groundpin = 18;             // analog input pin 4 -- ground
//const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);
  Serial.println("Begin ..... ");
  
  // Provide ground and power by using the analog inputs as normal
  // digital pins.  This makes it possible to directly connect the
  // breakout board to the Arduino.  If you use the normal 5V and
  // GND pins on the Arduino, you can remove these lines.
//  pinMode(groundpin, OUTPUT);
//  pinMode(powerpin, OUTPUT);
//  digitalWrite(groundpin, LOW); 
//  digitalWrite(powerpin, HIGH);

//Make sure the analog-to-digital converter takes its reference voltage from
  // the AREF pin
//  analogReference(EXTERNAL);

  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
}

void loop()
{

  Serial.print("X = ");
  Serial.print( analogRead(xpin));
  Serial.print("\t");

  //add a small delay between pin readings.  I read that you should
  //do this but haven't tested the importance
    delay(1); 

  Serial.print(" | Y = ");
  Serial.print( analogRead(ypin));
  Serial.print("\t");
  //add a small delay between pin readings.  I read that you should
  //do this but haven't tested the importance
    delay(1); 

  Serial.print(" | Z = ");
  Serial.print( analogRead(zpin));
  Serial.print("\n");  // delay before next reading:
  delay(2000);
}
