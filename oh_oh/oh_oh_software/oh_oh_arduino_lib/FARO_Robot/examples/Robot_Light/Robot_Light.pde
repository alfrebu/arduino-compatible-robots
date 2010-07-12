/************************************

attach one LDR to analogIn 0, another to analogIn 1
becareful of Vcc and Gnd

FARO_Robot->followLight():Robot will follow light;
FARO_Robot->escapeLight():Robot will escape light;

 ************************************
*/



#include <Servo.h>

#include <FARO_Robot.h>

FARO_Robot myRobot;



void setup(){
 //Serial.begin(9600);
 myRobot.calibrateLight();

}

void loop(){
 myRobot.escapeLight();
 //Serial.print("sl:");
 //Serial.print(myRobot.speedL);
 //Serial.print("sr:");
 //Serial.println(myRobot.speedR);

}
