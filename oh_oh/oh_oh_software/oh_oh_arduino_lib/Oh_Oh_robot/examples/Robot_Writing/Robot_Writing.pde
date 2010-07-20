/**************************************************

Write letters with Oh_Oh robot

steps:
1.upload this sketch
2.run processing sketch "Oh_Oh_Robot_Writing.pde"
3.wait until led 13 on board turned on,click on-
  bord button once.
4.wait until message "success" showing in processing
4.input the letters you want to write, length is 
  limitted according to the number of steps in total
5.unplug the robot, connect the battery or reset if 
  battery is connected.
6.wait until led 13 turned on, attach a marker/brush 
  pen to the servo in such an angle that its tip is 
  very close to ground(not touching).
7.put the robot in position, and click on board button
  twice.Wait until it begins.
8.each time after it writes a letter, put it in new 
  position and click the button once

Note:Calibrate it with "Oh_Oh_test_angle.pde" if the 
writing is not in shape


***************************************************/
#include <IRremote.h>
#include <IRremoteInt.h>

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
