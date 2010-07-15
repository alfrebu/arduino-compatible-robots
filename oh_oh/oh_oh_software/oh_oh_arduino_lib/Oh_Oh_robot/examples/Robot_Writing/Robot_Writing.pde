#include <MultiClick.h>

#include <Servo.h>

#include <EEPROM.h>

#include <FARO_Robot.h>

FARO_Robot myRobot;
MultiClick mc;


void setup(){
  pinMode(8,INPUT);
  digitalWrite(8,HIGH);
  myRobot.speedL=195;
  myRobot.getServo();
  myRobot.writingIni();
 // Serial.println("wtf");
  mc.ini(8);
}
void loop(){
 // Serial.println("1");
  mc.begin();
 // Serial.println(mc.clicks);
  myRobot.writeWithPen(mc.clicks);
}
