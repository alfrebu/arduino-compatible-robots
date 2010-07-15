#include "WProgram.h"
#include "Oh_Oh_Robot.h"
#include "../EEPROM/EEPROM.h"

#include "../Servo/Servo.h"


Oh_Oh_Robot::Oh_Oh_Robot()
{
	Oh_Oh_Robot::motor_1_1=3;//7,3--old/new
	Oh_Oh_Robot::motor_1_2=4;//8,4
	Oh_Oh_Robot::motor_1_PWM=9;//6,9
	Oh_Oh_Robot::motor_2_1=6;//4,6
	Oh_Oh_Robot::motor_2_2=7;//3,7
	Oh_Oh_Robot::motor_2_PWM=10;//5,10
	Oh_Oh_Robot::ledPin=13;
	Oh_Oh_Robot::button=8;
	Oh_Oh_Robot::speedL=255;
	Oh_Oh_Robot::speedR=255;

	Oh_Oh_Robot::LDR_L=2;
	Oh_Oh_Robot::LDR_R=1;
	

	pinMode(motor_1_1,OUTPUT);
	pinMode(motor_1_2,OUTPUT);
//	pinMode(motor_1_PWM,OUTPUT);
	pinMode(motor_2_1,OUTPUT);
	pinMode(motor_2_2,OUTPUT);
//	pinMode(motor_2_PWM,OUTPUT);

	//pinMode(ledPin,OUTPUT);
	//pinMode(button1,INPUT);
	//pinMode(button2,INPUT);
	
	pinMode(button,OUTPUT);
	digitalWrite(button,HIGH);
	
	powerFactor=1.0;
	sizeFactor=1.0;

	arrayPoint=0;
	runFlag=false;


	randomSeed(analogRead(3));
	//changeSpeed(255);

	oldValue_LDR=analogRead(LDR_L);

}


/*******************************************


Basic Functions

 *wheel control
 *servo control
 *LDR values

 
********************************************/

void Oh_Oh_Robot::forward()
{
	situation=1;
	turnLeftWheel(1);
	turnRightWheel(1);
//	digitalWrite(motor_1_1,LOW);
//	digitalWrite(motor_1_2,HIGH);
//	digitalWrite(motor_2_1,LOW);
//	digitalWrite(motor_2_2,HIGH);
}
void Oh_Oh_Robot::backward()
{
	situation=2;
	turnLeftWheel(-1);
	turnRightWheel(-1);
//	digitalWrite(motor_1_1,HIGH);
//	digitalWrite(motor_1_2,LOW);
//	digitalWrite(motor_2_1,HIGH);
//	digitalWrite(motor_2_2,LOW);
}
void Oh_Oh_Robot::left()
{
	situation=3;
	turnLeftWheel(-1);
	turnRightWheel(1);
//	digitalWrite(motor_1_1,HIGH);
//	digitalWrite(motor_1_2,LOW);
//	digitalWrite(motor_2_1,LOW);
//	digitalWrite(motor_2_2,HIGH);
}
void Oh_Oh_Robot::right()
{
	situation=4;
	turnLeftWheel(1);
	turnRightWheel(-1);
//	digitalWrite(motor_1_1,LOW);
//	digitalWrite(motor_1_2,HIGH);
//	digitalWrite(motor_2_1,HIGH);
//	digitalWrite(motor_2_2,LOW);

}
void Oh_Oh_Robot::stop()
{
	situation=0;
	turnLeftWheel(0);
	turnRightWheel(0);
//	digitalWrite(motor_1_1,LOW);
//	digitalWrite(motor_1_2,LOW);
//	digitalWrite(motor_2_1,LOW);
//	digitalWrite(motor_2_2,LOW);
}
void Oh_Oh_Robot::changeSpeed(int spd, int wheel){
	if(wheel & 0x01){
		speedL=spd;
		analogWrite(motor_1_PWM,spd);
	}
	if(wheel>>1 & 0x01){
		speedR=spd;
		analogWrite(motor_2_PWM,spd);
	}
}


void Oh_Oh_Robot::onOff(bool flag, int wheel){
	if(wheel & 0x01){
		speedL=flag;
		digitalWrite(motor_1_PWM,flag);
	}
	if(wheel>>1 & 0x01){
		speedR=flag;
		digitalWrite(motor_2_PWM,flag);
	}
}
void Oh_Oh_Robot::onOffMode(){
	pinMode(motor_1_PWM,OUTPUT);
	pinMode(motor_2_PWM,OUTPUT);
}



void Oh_Oh_Robot::turnLeftWheel(int dir){
	if(dir<0){
		digitalWrite(motor_1_1,HIGH);
		digitalWrite(motor_1_2,LOW);	
	}else if(dir>0){
		digitalWrite(motor_1_1,LOW);
		digitalWrite(motor_1_2,HIGH);
	}else if(dir==0){
		digitalWrite(motor_1_1,LOW);
		digitalWrite(motor_1_2,LOW);
	}
}
void Oh_Oh_Robot::turnRightWheel(int dir){
	if(dir<0){
		digitalWrite(motor_2_1,HIGH);
		digitalWrite(motor_2_2,LOW);	
	}else if(dir>0){
		digitalWrite(motor_2_1,LOW);
		digitalWrite(motor_2_2,HIGH);
	}else if(dir==0){
		digitalWrite(motor_2_1,LOW);
		digitalWrite(motor_2_2,LOW);
	}
}

//******************************************* Servo functions

void Oh_Oh_Robot::getServo(int n){
	
	presetArm(80,110);
	arm.attach(n);
}
void Oh_Oh_Robot::liftArm(){
	armPosition=1;
	arm.write(liftAngle);
}
void Oh_Oh_Robot::dropArm(){
	armPosition=0;
	arm.write(dropAngle);
}
void Oh_Oh_Robot::waveArm(){
	int count=2;
	dropArm();
	while(count){
		for(int i=liftAngle;i>dropAngle;i-=2){
			moveArm(i);
			Serial.println(arm.read());
			delay(10);
		}
		for(int i=dropAngle;i<liftAngle;i+=2){
			moveArm(i);
			delay(10);
		}
		count--;
	}

}
void Oh_Oh_Robot::presetArm(int dropAngle, int liftAngle){
	this->dropAngle=dropAngle;
	this->liftAngle=liftAngle;
}

void Oh_Oh_Robot::moveArm(int angle){
	armPosition=2;
	arm.write(angle);
}


//*********************************************** LDR functions


void Oh_Oh_Robot::calibrateLight(){
	LDR_thresholdL=analogRead(LDR_L);
	LDR_thresholdR=analogRead(LDR_R);
}

void Oh_Oh_Robot::LDR_getValues(){
	LDR_sensL=analogRead(LDR_L);
	LDR_sensR=analogRead(LDR_R);
}