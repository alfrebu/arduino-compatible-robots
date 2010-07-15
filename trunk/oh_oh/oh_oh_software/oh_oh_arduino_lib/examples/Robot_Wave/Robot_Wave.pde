/*********************************
"Wave" here means wave hand
When waving your hand in front of the robot's LDR sensor, it'll wave back

attach servo to FARO robot's servo port
attach a LDR o analogIn 0

call FARO_Robot->getServo() to initialize servo
call FARO_Robot->sayHi() in each loop to determin 



***********************************/



#include <Servo.h>

#include <FARO_Robot.h>

FARO_Robot myRobot;

void setup(){
  myRobot.getServo();

}
void loop(){

  myRobot.sayHi();
  delay(40);
}
