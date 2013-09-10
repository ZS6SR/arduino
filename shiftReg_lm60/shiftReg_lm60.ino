/*
Basic Digital Output - Dual Shift Register #4
 This example uses 3 Digital Output Pins to Control 16 Digital Output Signals from Dual Shift Registers
 8 LED are on the outputs on each the Shift Registers.
 This example will do a 16 LED Knight Rider Sweep.
 Author: David M. Auld
 Date: 14th October 2009
 */
int dataPin = 2;              // The Serial Data Pin to the Shift Register (14)
int latchPin = 3;             // The Latch Pin to the Shift Register (12)
int clockPin = 4;             // The Clock Pin to the Shift Register (11)

int value = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;

//int seq2[30] = {128,64,32,16,8,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,4,8,16,32,64};
int seq[63] = {
  1,2,4,8,16,32,64,128
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,64,32,16,8,4,2,1};
//int seq[31]= {0,0,0,0,0,0,0,0,128,64,32,16,8,4,2,1,2,4,8,16,32,64,128,0,0,0,0,0,0,0,0};
int seq2[64]= {
  0,0,0,0,0,0,0,0
    ,1,2,4,8,16,32,64,128
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,128,64,32,16,8,4,2,1
    ,0,0,0,0,0,0,0,0};

int seq3[64]= {
  0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,1,2,4,8,16,32,64,128
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,128,64,32,16,8,4,2,1
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0};

int seq4[64]= {
  0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,1,2,4,8,16,32,64,128
    ,128,64,32,16,8,4,2,1
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0};
void setup()
{
  pinMode(dataPin, OUTPUT);    // Configure Digital Pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{  
  //Get Temp from both sensors
  Serial.print("Temp2: ");
  float temp1 = getTemp(getVolts(A2));
  Serial.println(temp1);
  Serial.print("Temp1: ");
  float temp2 = getTemp(getVolts(A1));
  Serial.println(temp2);
  Serial.println("-----------------------------------------------------------");
  Serial.print("Temp: "); Serial.println((temp1 + temp2) / 2);
  Serial.println("-----------------------------------------------------------");
  
  // sweep LEDs using shift registers
  for (int n=0; n < 64; n++)
  {
    value4 = seq[n];
    value3 = seq2[n];
    value2 = seq3[n];
    value = seq4[n];

    writeOutput();
    delay(50);
  }
}

void writeOutput()
{
  digitalWrite(latchPin, LOW);                       // Pull latch LOW to send data
  shiftOut(dataPin, clockPin, MSBFIRST, value);      // Send the data byte 1
  shiftOut(dataPin, clockPin, MSBFIRST, value2);     // Send the data byte 2
  shiftOut(dataPin, clockPin, MSBFIRST, value3);     // Send the data byte 2
  shiftOut(dataPin, clockPin, MSBFIRST, value4);     // Send the data byte 2
  digitalWrite(latchPin, HIGH);                      // Pull latch HIGH to stop sending data
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
  
  float volts;
  volts = (((float)smallT / 1024) * 5000);
  
  Serial.print("Input Value: ") ; Serial.print(inputValue);
  Serial.print(" | Voltage: ") ; Serial.print(volts);
  Serial.println();
  return volts;
  
}

float getTemp(float volts)
{
  //float temp = (volts - 0.5) / 0.01;
  float temp = 0;
  temp = (volts - 424) / 6.25;
//  Serial.print(" | Temperature: "); Serial.print(temp); Serial.print(" 'C");
  return temp;
}



