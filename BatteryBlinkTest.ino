/***********************************************************/
//Demo for the the Battery Display by Catalex
//Hardware: Battery Display *1
//Board:  Arduino Mega 2560
//IDE:    Arduino-1.0
//Function:  The Battery Display blinks once per second.
//Store: http://www.aliexpress.com/store/1199788
//          http://www.dx.com/
/***************************************************************/

const byte clkPin = 10, //pins definitions for TM1651 and can be changed to other ports       
  dataPin = 11,
  brightTypical = 2,
  brightest = 7,
  addrAuto = 0x40,
  addrFixed = 0x44;
  
const bool frameOn = 1, 
  frameOff = 0;

static int8_t levelTab[] = {0x00,0x01,0x03,0x07,0x0f,0x1f};//Level 0~5

byte Cmd_SetData,
  Cmd_SetAddr,
  Cmd_DispCtrl;
  
//TM1651 batteryDisplay(clkPin, dataPin);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BatteryBlinkTest.ino");

  delay(1000);

  pinMode(clkPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //Serial.println("Battery Display Pin Modes Set");
  
  setBDsplyBrightness(brightTypical, 0x40, 0xc0);
  delay(1000);

  clearBDsply();
  
  //Serial.println("Battery Display Initialized");
  
  //setBDsplyBrightness(brightest);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

void setBDsplyBrightness(byte brightness, byte setData, byte setAddr)
{
  Cmd_SetData = setData;
  Cmd_SetAddr = setAddr;
  Cmd_DispCtrl = 0x88 + brightness; // Set the brightness and it takes effect the next time it displays.

  //Serial.println("Battery Display Brightness Set");
}

void clearBDsply()
{
  bDsplyLevel(0);

  bDsplyFrame(frameOff);

  //Serial.println("Battery Display Cleared");
}

void bDsplyLevel(byte level)
{
  if(level > 5) return;
  
  startBDsply();

  writeByteToBDsply(addrFixed);
  writeByteToBDsply(levelTab[level]);

  stopBDsply();
}

void startBDsply()
{
  Serial.println("===Start Battery Display===");
  
  digitalWrite(clkPin, HIGH);
  digitalWrite(dataPin, HIGH);

  delayMicroseconds(2);

  digitalWrite(dataPin, LOW);
  digitalWrite(clkPin, LOW);

  //Serial.println("Battery Display Started");
}

//End of transmission
void stopBDsply()
{
  Serial.println("===Stop Battery Display===");
  
  digitalWrite(clkPin,LOW);
 // delayMicroseconds(2);
  digitalWrite(dataPin,LOW);
//  delayMicroseconds(2);

  digitalWrite(clkPin,HIGH);
 // delayMicroseconds(2);
  digitalWrite(dataPin,HIGH); 

  //Serial.println("Battery Display Stopped");
}

void writeByteToBDsply(byte wrData)
{
  uint8_t i, count1;   

  //Serial.println("===Write Byte to Battery Display===");
  
  for(i=0; i<8; i++)        //sent 8-bit data
  {
//    Serial.print("bit ");
//    Serial.println(i+1);  
    
    digitalWrite(clkPin, LOW);  
    delayMicroseconds(3);
//    Serial.println("Battery Display Clk pin set LOW");  
//    Serial.print("digitalRead(clkPin): ");
//    Serial.println(digitalRead(clkPin)); 
      
    if(wrData & 0x01) 
    {
      digitalWrite(dataPin, HIGH); //LSB first
      delayMicroseconds(3);
      //Serial.println("Battery Display Data pin set HIGH");  
    }
    else 
    {
      digitalWrite(dataPin, LOW);
      delayMicroseconds(3);
      //Serial.println("Battery Display Data pin set LOW"); 
    }

//    Serial.print("digitalRead(dataPin): ");
//    Serial.println(digitalRead(dataPin));  
    
    wrData >>= 1;    
      
    digitalWrite(clkPin, HIGH);
    delayMicroseconds(3);
//    Serial.println("Battery Display Clk pin set HIGH");  
//    Serial.print("digitalRead(clkPin): ");
//    Serial.println(digitalRead(clkPin)); 
  }  
  
  digitalWrite(clkPin, LOW); //wait for the ACK
  delayMicroseconds(3);
//  Serial.println("Battery Display Clk pin set LOW");  
//  Serial.print("digitalRead(clkPin): ");
//  Serial.println(digitalRead(clkPin)); 
  
  digitalWrite(dataPin, HIGH);
  delayMicroseconds(3);
//  Serial.println("Battery Display Data pin set HIGH"); 
//  Serial.print("digitalRead(dataPin): ");
//  Serial.println(digitalRead(dataPin));  
  
  digitalWrite(clkPin, HIGH); 
  delayMicroseconds(3);  
//  Serial.println("Battery Display Clk pin set HIGH"); 
//  Serial.print("digitalRead(clkPin): ");
//  Serial.println(digitalRead(clkPin));  
    
  pinMode(dataPin, INPUT);
  delayMicroseconds(3);
//  Serial.println("Battery Display Data pin mode INPUT"); 
//  Serial.print("digitalRead(dataPin): ");
//  Serial.println(digitalRead(dataPin));
    
  while(digitalRead(dataPin))    
  { 
    count1 += 1;
//    Serial.print("count1: ");
//    Serial.println(count1);
    
    if(count1 == 200)//
    {
     pinMode(dataPin,OUTPUT);
     delayMicroseconds(3);
//     Serial.println("Battery Display Data pin mode OUTPUT"); 
//     Serial.print("digitalRead(dataPin): ");
//     Serial.println(digitalRead(dataPin)); 
     
     digitalWrite(dataPin,LOW);
     delayMicroseconds(3);
//     Serial.println("Battery Display Data pin set LOW"); 
//     Serial.print("digitalRead(dataPin): ");
//     Serial.println(digitalRead(dataPin)); 
     
     count1 = 0;
    }
    
    pinMode(dataPin, INPUT);
    delayMicroseconds(3);
//    Serial.println("Battery Display Data pin mode INPUT"); 
//    Serial.print("digitalRead(dataPin): ");
//    Serial.println(digitalRead(dataPin)); 
  }
  
  pinMode(dataPin, OUTPUT);
  delayMicroseconds(3);
//  Serial.println("Battery Display Data pin mode OUTPUT");
//  Serial.print("digitalRead(dataPin): ");
//  Serial.println(digitalRead(dataPin));  
//
//  Serial.println("Byte Written to Battery Display");
}

void bDsplyFrame(bool frameFlag)
{
  byte segData;

  if(frameFlag) segData = 0x40;
  else segData = 0x00;

  startBDsply();

  writeByteToBDsply(addrAuto);

  for(byte i=0; i < 3; i++)
    writeByteToBDsply(segData);

  stopBDsply();
}

void loop()
{
  blink();
}

void blink()
{
  //Serial.println("======Blink======");
  bDsplyLevel(5);
  bDsplyFrame(frameOn);
  delay(1000);
  
  bDsplyLevel(0);
  bDsplyFrame(frameOff);
  delay(1000);
}
