#include "WProgram.h"
#include "Oh_Oh_Robot.h"

#include "../Servo/Servo.h"

/*****************************************

running robot according to a preset script


*****************************************/


void Oh_Oh_Robot::run(int span){
	if(runFlag){
		if(millis()-runTimer>=timeSpan[arrayPoint]*powerFactor*sizeFactor){

			arrayPoint++;
			stop();
			delay(span);
			changeAction();
			runTimer=millis();
			
		}
	}else{
		arrayPoint=0;
		stop();
	}
}

void Oh_Oh_Robot::changeAction(){
	switch(direction[arrayPoint]){
		case 0:
			stop();
		break;
		case 1:
			forward();
		break;
		case 2:
			backward();
		break;
		case 3:
			left();
		break;
		case 4:
			right();
		break;
		case 5:
			stop();
			liftArm();
		break;
		case 6:
			stop();
			dropArm();
		break;
		case 7:
			while(digitalRead(button)){
				
			}
		break;
		case 255:
			runFlag=false;
			stop();
		break;
	}

}

