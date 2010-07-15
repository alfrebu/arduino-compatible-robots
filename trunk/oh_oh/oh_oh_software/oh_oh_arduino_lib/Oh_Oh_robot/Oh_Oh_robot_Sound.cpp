#include "WProgram.h"
#include "Oh_Oh_Robot.h"

#include "../Servo/Servo.h"

/********************************************

example using microphone on board



********************************************/

void Oh_Oh_Robot::startRandomRun(){
	randomfillArray();
	runTimer=millis();
	arrayPoint=0;
	changeSpeed(speedL,1);
	changeSpeed(speedR,2);
	runFlag=true;

}

void Oh_Oh_Robot::stopRandomRun(){
	runFlag=false;
}
void Oh_Oh_Robot::randomfillArray(){
	direction[0]=random(4)+1;
	timeSpan[0]=0;
	for(int i=1;i<100;i++){
		direction[i]=random(4)+1;
		timeSpan[i]=random(100,1000);
	}
}

