/*******************************************************

Infrared Remote Control

You can change the preset signals of different keys in 
iniIR(), see class discription for details.

"vol" up & down for forward and backward, "ch" up & down 
for turn left and turn right

use "mute" button to mute between servo and move mode, in
servo mode you can lift or drop servo by pressing the keys 
for "turn left" & "turn right"

press "TV" button to see some special effects

********************************************************/


#include <Servo.h>

#include <Oh_Oh_Robot.h>

Oh_Oh_Robot myRobot;

void setup(){
  Serial.begin(9600);
  myRobot.iniIR();
  myRobot.onOffMode();
  myRobot.onOff(true);

  myRobot.getServo();
  
}
void loop(){
  myRobot.runIR();
  myRobot.moveArmSlow();
}
