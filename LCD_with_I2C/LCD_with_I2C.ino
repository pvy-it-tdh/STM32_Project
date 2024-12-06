#include<HardwareTimer.h> 
#define LED PA1
#define INTERVAL1 1000000
HardwareTimer Timer1(TIM1);
void ngat1()
{
  int state= digitalRead(LED);
  if(state==HIGH)
  {
    digitalWrite(LED,LOW);
  }
  else{
    digitalWrite(LED,HIGH);
  }
}
void setup()
{
  pinMode(LED,OUTPUT);
  Timer1.pause();
  Timer1.setOverflow(INTERVAL1,MICROSEC_FORMAT);
  Timer1.attachInterrupt(ngat1);
  Timer1.resume();
}
void loop()
{
  
}