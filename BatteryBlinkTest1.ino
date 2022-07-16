/***********************************************************/
//Demo for the the Battery Display by Catalex
//Hardware: Battery Display *1
//Board:  Arduino UNO R3
//IDE:    Arduino-1.0
//Function:  The Battery Display blinks once per second.
//Store: http://www.aliexpress.com/store/1199788
//          http://www.dx.com/
/***************************************************************/

#include "TM1651.h"
#define CLK 10//pins definitions for TM1651 and can be changed to other ports       
#define DIO 11
TM1651 batteryDisplay(CLK,DIO);
void setup()
{
  batteryDisplay.init();
  Serial.println("Battery Display Initialized");
  batteryDisplay.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  Serial.println("Battery Display Set");
}
void loop()
{
  blink();
}
void blink()
{
  batteryDisplay.displayLevel(5);
  batteryDisplay.frame(FRAME_ON);
  delay(1000);
  batteryDisplay.displayLevel(0);
  batteryDisplay.frame(FRAME_OFF);
  delay(1000);
}
