/*********************************

when blowing/shouting or making big
noise to the microphone, led on pin
13 will light up


**********************************/

#include <SoundSwitch.h>

SoundSwitch mySwitch(4);

void setup(){
  pinMode(13,OUTPUT);
  mySwitch.setThreshold(20);
}
void loop(){
  mySwitch.checkState();
  digitalWrite(13,mySwitch.isOn);
}
