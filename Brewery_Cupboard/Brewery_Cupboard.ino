int sensorPin1 = 1;
int LED = 5;
int FAN = 3;
int HighCount = 0;
int LowCount = 0;
unsigned long count = 0;

// for LM60 sensor
float displayVal = 0;
int t_next = 1; //start 1
float tempArray[10];

void setup() {
  Serial.begin(38400);
  pinMode(LED, OUTPUT); //set the LED pin as OUTPUT
  pinMode(FAN, OUTPUT); //set the LED pin as OUTPUT
  digitalWrite(FAN, LOW);
  digitalWrite(LED, LOW);  
}

void loop() {
//  int reading1 = 0;
//  for ( int i=0; i<99;  i=i+1) {
//    reading1 = reading1 + analogRead(sensorPin1);  
//  }
//  Serial.print("Reading1 = ");  Serial.println(reading1/99);
//  
// // converting that reading to voltage, for 3.3v arduino use 3.3
// float mv = (float)(reading1/99)*5/1023;
// Serial.print(mv, 3); Serial.println(" mV");  
// 
// 
// // now print out the temperature
// float tempC1 = ( ( mv * 1024) - 424 ) / 6.25;
// Serial.print(tempC1); Serial.println(" C");
// if (tempC1 > 33) {
//    HighCount++;
//    Serial.print("HighCount = "), Serial.println(HighCount);
//    if (HighCount >= 5) {
//      LowCount = 0;
//       digitalWrite(LED, HIGH); //write 1 or HIGH to led pin
//       digitalWrite(FAN, HIGH); //write 1 or HIGH to fan pin
//    }
//  } else { 
//      LowCount++;
//      Serial.print("LowCount = "), Serial.println(LowCount);
//      if ((LowCount >= 10) && (tempC1 < 29)) {
//      HighCount = 0;
//      digitalWrite(LED, LOW);  //write 0 or low to led pin
//      digitalWrite(FAN, LOW);  //write 0 or low to fan pin     
//    }
//  } 

 delay(1000);
 Serial.println("===================================================");
 Serial.print("Count = ");  Serial.println(count);
 int sensorVal = analogRead(sensorPin1);
 Serial.print("sensorVal = ");  Serial.println(sensorVal);
 float temp = modTemp(sensorVal);
  
  if(count > 10){
    if(displayVal == 0){
      displayVal = getAverageTemp();
      Serial.print("Temp: "); Serial.println(displayVal);
      
    }else{

      bool res = isDisplayChange();
      if(res == 1){
        displayVal = getAverageTemp(); //displayVal update
      }
      Serial.print("Temp: "); Serial.println(displayVal);
    }
  }
    if (displayVal > 32) {
      HighCount++;
      Serial.print("HighCount = "), Serial.println(HighCount);
      if (HighCount >= 5) {
        LowCount = 0;
        digitalWrite(LED, HIGH); //write 1 or HIGH to led pin
        digitalWrite(FAN, HIGH); //write 1 or HIGH to fan pin
      }
    } else { 
      LowCount++;
      Serial.print("LowCount = "), Serial.println(LowCount);
      if ((LowCount >= 10) && (displayVal < 29)) {
        HighCount = 0;
        digitalWrite(LED, LOW);  //write 0 or low to led pin
        digitalWrite(FAN, LOW);  //write 0 or low to fan pin     
      }
    
  }
  
  tempArray[t_next] = temp;
  t_next ++;
  if(t_next == 10){
    t_next = 0;
  }
  count ++;
  delay(10);
}

float getAverageTemp(){
  float sum = 0;
  for(int i=0; i<=9; i++){
    sum += tempArray[i];
  }
  float ave = sum / 10;
  return ave;
}

float modTemp(int sensor_value){
  // for LM60. offset 424mv (0C), +6.25mv/C
  float temp = ((5.0 * sensor_value) / 1024) * 1000; //mV
  temp = (temp - 424) / 6.25; //C
  return temp;
}

boolean isDisplayChange(){
  //change display value sensitivity: 0.5

  float ave = getAverageTemp();
  float val1 = displayVal - ave;
  float val2 = ave - displayVal;
  
  if(val1 >= 0){
    // in increase
    if(val1 >= 0.5){
      return true;
    }else{
      return false;
    }
  }else{
    // in decrease
    if(val2 >= 0.5){
      return true;
    }else{
      return false;
    }
  }
}


