/*
Basic Digital Output - Dual Shift Register #1
This example uses 3 Digital Output Pins to Control 16 Digital Output Signals from Dual Shift Registers
8 LED are on the outputs on each the Shift Registers.
This example will do the Knight Rider [2009 model kitt] dual light sweep (out to in and back).
Author: David M. Auld
Date: 14th October 2009
*/
int dataPin = 2;              // The Serial Data Pin to the Shift Register
int latchPin = 3;             // The Latch Pin to the Shift Register
int clockPin = 4;             // The Clock Pin to the Shift Register
int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2};
int seq2[14] = {128,64,32,16,8,4,2,1,2,4,8,16,32,64};
int value = 0;
int value2 = 0;
void setup()
{
  pinMode(dataPin, OUTPUT);    // Configure Digital Pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);  
}
void loop() 
{
    for (int n=0; n < 14; n++)
    {
      value = seq[n];             //Forward array
      value2 = seq2[n];          //Reverse array
      writeOutput();
      delay(75);
    }
}
void writeOutput()
{
    digitalWrite(latchPin, LOW);                       // Pull latch LOW to send data
    shiftOut(dataPin, clockPin, MSBFIRST, value);      // Send the data byte 1
    shiftOut(dataPin, clockPin, MSBFIRST, value2);     // Send the data byte 2
    digitalWrite(latchPin, HIGH);                      // Pull latch HIGH to stop sending data
}

