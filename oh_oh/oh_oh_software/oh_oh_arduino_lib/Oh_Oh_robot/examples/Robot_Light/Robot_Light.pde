/************************************

attach one LDR to analogIn 0, another to analogIn 1
becareful of Vcc and Gnd

Oh_Oh_Robot->followLight():Robot will follow light;
Oh_Oh_Robot->escapeLight():Robot will escape light;

 ************************************
*/



#include <Servo.h>

#include <Oh_Oh_Robot.h>

Oh_Oh_Robot myRobot;



void setup(){

 myRobot.calibrateLight();

}

void loop(){
// myRobot.escapeLight();
 myRobot.followLight();

}
