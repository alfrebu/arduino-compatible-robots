/*********************************************************

multi-click button

will hold the value of how many times the button is clicked.
is a serial process, interrputs program flow
1 second(preset value) after the final click, interrpution 
is released,and you can use its value


**********************************************************/

#include <MultiClick.h>

MultiClick mc;

int buttonPin=8;
int ledPin=13;

void setup(){
  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin,HIGH);// if button is only connected to ground
  mc.ini(buttonPin);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
}
void loop(){
  mc.begin();
  for(int i=0;i<mc.clicks;i++){
    digitalWrite(ledPin,HIGH);
    delay(300);
    digitalWrite(ledPin,LOW);
    delay(300);
  }
}
