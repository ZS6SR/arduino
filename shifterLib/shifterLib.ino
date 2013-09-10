#include <Shifter.h>

#define SER_Pin 2 //SER_IN (Data Pin)
#define RCLK_Pin 3 //L_CLOCK ((Latch)
#define SRCLK_Pin 4 //CLOCK (Clock)

#define NUM_REGISTERS 4 //how many registers are in the chain


//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 

void setup(){

}

void loop(){
  shifter.clear(); //set all pins on the shift register chain to LOW
  shifter.write(); //send changes to the chain and display them
    
//  delay(1000);
  
  for (int i = 0; i < 32; i++)
  {
    shifter.setPin(i, HIGH);
//    shifter.setPin(i + 2, HIGH);
    shifter.write();
    delay(50);
    shifter.setPin(i, LOW);
//    shifter.setPin(i + 2, HIGH);
  }
  
  for (int j = 32; j > 0; j--)
  {
    shifter.setPin(j, HIGH);
    shifter.write();
    delay(50);
    shifter.setPin(j, LOW);
  }

//  shifter.setPin(0, HIGH); //set pin 1 in the chain(second pin) HIGH
//  shifter.setPin(2, HIGH);
//  shifter.setPin(4, HIGH);
//  shifter.setPin(6, HIGH);
//  shifter.setPin(17, HIGH);
 
//  shifter.write(); //send changes to the chain and display them
  //notice how you only call write after you make all the changes you want to make
  
//  delay(1000);
  
  
//  shifter.setAll(HIGH); //Set all pins on the chain high
//  shifter.write(); //send changes to the chain and display them
  
//  delay(1000);
  
}
