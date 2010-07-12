/*********************************
Works with SoundSwitch to determin the noise level
attach sound detector's ouput to analogIn 0

SoundSwitch constructor has two paraments, first is the analogIn pin it's using,
second is the noise threshold, defaulted by 100;
call SoundSwitch->checkState every loop to get sound values;
if determins enough noise, SoundSwitch->isOn will be true;
Otherwize it will be false;
By the right time it's turned on/off, isTurnningOn/isTurnningOff will be true

call FARO_Robot->startRandomRun() will generate 100 random action orders,
(action, duration) and put into its order list
call FARO_Robot->stopRandomRun() to stop running

call FARO_Robot->run() each loop to get robot running according to its 
order list or keep still

*********************************/


#include <Servo.h>

#include <FARO_Robot.h>

#include <SoundSwitch.h>

SoundSwitch mySwitch(0);
FARO_Robot myRobot;

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}
void loop(){
  mySwitch.checkState();
  digitalWrite(13,mySwitch.isOn);
  if(mySwitch.isTurnningOn){
    myRobot.startRandomRun();
  }
  if(mySwitch.isTurnningOff){
    myRobot.stopRandomRun();
  }
  
  myRobot.run();
  delay(10);
}
