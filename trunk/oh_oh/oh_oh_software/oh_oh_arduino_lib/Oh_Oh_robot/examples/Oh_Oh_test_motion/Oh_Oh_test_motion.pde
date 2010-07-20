/**************************************************************

Testing forward,backward,left,right functions of Oh_Oh robot

After uploading, click the on-board button to start the robot
and switch between different actions


***************************************************************/

#include <Oh_Oh_Robot.h>

#include <Servo.h>





Oh_Oh_Robot myRobot;

void setup(){
  boolean old=true;
  int state=0;
  pinMode(8,INPUT);
  digitalWrite(8,HIGH);
  
  //myRobot.getServo();
  myRobot.changeSpeed(255);
  //myRobot.onOffMode();
  //myRobot.onOff(true);
  while(true){
    if(!digitalRead(8) && old){
      state++;
      switch(state){
        case 0:
         myRobot.stop();
        break;
        case 1:
         myRobot.forward();
        break;
        case 2:
         myRobot.backward();
        break;
        case 3:
         myRobot.left();
        break;
        case 4:
         myRobot.right();
         state=-1;
        break; 
      }
    }
    old=digitalRead(8);
  }
}
void loop(){
 //analogWrite(9,255);
 // myRobot.right();
 /* delay(217);
  myRobot.stop();
  delay(3000);
  myRobot.right();
  delay(217);
  myRobot.stop();
  delay(3000);*/
}
