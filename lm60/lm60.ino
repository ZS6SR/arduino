
void setup()
{
  
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
  //Get Temp from both sensors
//  Serial.print("Temp1: ");
  float temp1 = getTemp(getVolts(A1));
//  Serial.println(temp1);
//  Serial.print("Temp2: ");
  float temp2 = getTemp(getVolts(A2));
//  Serial.println(temp2);
  float temp3 = getTemp(getVolts(A3));
  Serial.println();
  Serial.print("Temp: "); Serial.println((temp0 + temp1 + temp2 + temp3) / 4);
  Serial.println();
  delay(1000);
}
