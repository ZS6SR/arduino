int sensorPin = 4;    				// select the input pin for the photocell
int sensorValue = 0;  				// variable to store the value coming from the photocell

void setup() {
  Serial.begin(9600); 				//Set baud rate to 9600 on the Arduino
}

void loop() {
                                          // read the value from the sensor:
  sensorValue = analogRead(sensorPin);  //get the voltage value from input pin
  Serial.print("Light Sensor: ");
  Serial.println(sensorValue); 		 //print the value to Serial monitor
  delay(1000);                        //delay for 1 seconds
}
