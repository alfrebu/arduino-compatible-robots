/************************************************

Use this sketch to calibrate for writing function

NOTE: try to use new batteries!

connect the battery, put robot on round and mark 
the initial direction. when led 13 on board lights
up, press on borad button and wait until the robot
turns.mark the current direction, and meansure the 
degrees(d) it turned, use this formula:
  
  y=(0.242*90)/d

change the RU value in processing sketch 
"Oh_Oh_Robot_Writing.pde" with y.

************************************************/
#include <IRremote.h>
#include <IRremoteInt.h>

#include <Servo.h>

#include <Oh_Oh_Robot.h>

Oh_Oh_Robot myRobot;
int buttonPin=8;
int ledPin=13;

void setup(){
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);
  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin,HIGH);
  myRobot.changeSpeed(255);
  myRobot.stop();
  while(true){
    if(!digitalRead(buttonPin)){
      digitalWrite(ledPin,LOW);
      myRobot.stop();
      delay(1000);
      myRobot.left();
      delay(int(0.242*90*10));
      myRobot.stop();
      delay(1000);
      digitalWrite(ledPin,HIGH);
    }
  }
}
void loop(){
  
}
