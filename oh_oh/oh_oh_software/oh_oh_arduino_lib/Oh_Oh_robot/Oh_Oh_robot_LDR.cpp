#include "WProgram.h"
#include "Oh_Oh_Robot.h"

#include "../Servo/Servo.h"


/**************************************************

examples using LDR

 *follow
 *escape light 
 *wave arm

**********************************************/


void Oh_Oh_Robot::followLight(){
	LDR_getValues();

	int vL=map(LDR_sensL,0,LDR_thresholdL*0.9,255,95);
	int vR=map(LDR_sensR,0,LDR_thresholdR*0.9,255,95);
	LDR_sensL>LDR_thresholdL?vL=0:0;
	LDR_sensR>LDR_thresholdR?vR=0:0;
	//valueL<LDR_thresholdL*0.9?speedL=255:speedL=0;
	//valueR<LDR_thresholdR*0.9?speedR=255:speedR=0;

	forward();  
	changeSpeed(vL,1);
	changeSpeed(vR,2);
}


void Oh_Oh_Robot::escapeLight(){
	LDR_getValues();

	int vL=map(LDR_sensR,0,LDR_thresholdR*0.9,255,95);
	int vR=map(LDR_sensL,0,LDR_thresholdL*0.9,255,95);
	LDR_sensR>LDR_thresholdR?vL=0:0;
	LDR_sensL>LDR_thresholdL?vR=0:0;
	//valueL<LDR_thresholdL*0.9?speedL=255:speedL=0;
	//valueR<LDR_thresholdR*0.9?speedR=255:speedR=0;

	backward();  
	changeSpeed(vL,1);
	changeSpeed(vR,2);
}


void Oh_Oh_Robot::sayHi(int LDRsensitivity, int number){
	if(abs(analogRead(LDR_L)-oldValue_LDR)>=LDRsensitivity){
		counter_sayHi++;
		if(counter_sayHi>=number){
			waveArm();
			counter_sayHi=0; 
		}
	}
	oldValue_LDR=analogRead(LDR_L);

}
