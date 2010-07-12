#include "WProgram.h"
#include "FARO_Robot.h"
#include "../EEPROM/EEPROM.h"

#include "../Servo/Servo.h"


FARO_Robot::FARO_Robot()
{
	FARO_Robot::motor_1_1=4;
	FARO_Robot::motor_1_2=3;
	FARO_Robot::motor_1_PWM=5;
	FARO_Robot::motor_2_1=7;
	FARO_Robot::motor_2_2=8;
	FARO_Robot::motor_2_PWM=6;
	FARO_Robot::ledPin=13;
	FARO_Robot::pushButton;
	FARO_Robot::button1=12;
	FARO_Robot::button2=11;


	FARO_Robot::LDR_L=3;
	FARO_Robot::LDR_R=2;
	

	pinMode(motor_1_1,OUTPUT);
	pinMode(motor_1_2,OUTPUT);
//	pinMode(motor_1_PWM,OUTPUT);
	pinMode(motor_2_1,OUTPUT);
	pinMode(motor_2_2,OUTPUT);
//	pinMode(motor_2_PWM,OUTPUT);

	pinMode(ledPin,OUTPUT);
	pinMode(button1,INPUT);
	pinMode(button2,INPUT);

	powerFactor=1.0;
	sizeFactor=1.0;

	arrayPoint=0;
	runFlag=false;


	randomSeed(analogRead(3));
	changeSpeed(255);

	oldValue_LDR=analogRead(LDR_L);

}


void FARO_Robot::forward()
{
	situation=1;
	turnLeftWheel(1);
	turnRightWheel(1);
//	digitalWrite(motor_1_1,LOW);
//	digitalWrite(motor_1_2,HIGH);
//	digitalWrite(motor_2_1,LOW);
//	digitalWrite(motor_2_2,HIGH);
}
void FARO_Robot::backward()
{
	situation=2;
	turnLeftWheel(-1);
	turnRightWheel(-1);
//	digitalWrite(motor_1_1,HIGH);
//	digitalWrite(motor_1_2,LOW);
//	digitalWrite(motor_2_1,HIGH);
//	digitalWrite(motor_2_2,LOW);
}
void FARO_Robot::left()
{
	situation=3;
	turnLeftWheel(-1);
	turnRightWheel(1);
//	digitalWrite(motor_1_1,HIGH);
//	digitalWrite(motor_1_2,LOW);
//	digitalWrite(motor_2_1,LOW);
//	digitalWrite(motor_2_2,HIGH);
}
void FARO_Robot::right()
{
	situation=4;
	turnLeftWheel(1);
	turnRightWheel(-1);
//	digitalWrite(motor_1_1,LOW);
//	digitalWrite(motor_1_2,HIGH);
//	digitalWrite(motor_2_1,HIGH);
//	digitalWrite(motor_2_2,LOW);

}
void FARO_Robot::stop()
{
	situation=0;
	turnLeftWheel(0);
	turnRightWheel(0);
//	digitalWrite(motor_1_1,LOW);
//	digitalWrite(motor_1_2,LOW);
//	digitalWrite(motor_2_1,LOW);
//	digitalWrite(motor_2_2,LOW);
}
void FARO_Robot::changeSpeed(int spd, int wheel){
	if(wheel & 0x01){
		speedL=spd;
		analogWrite(motor_1_PWM,spd);
	}
	if(wheel>>1 & 0x01){
		speedR=spd;
		analogWrite(motor_2_PWM,spd);
	}
}


void FARO_Robot::turnLeftWheel(int dir){
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
void FARO_Robot::turnRightWheel(int dir){
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
void FARO_Robot::getServo(){
	

	arm.attach(10);
}
void FARO_Robot::liftArm(){
	armPosition=1;
	arm.write(80);
}
void FARO_Robot::dropArm(){
	armPosition=0;
	arm.write(110);
}
void FARO_Robot::waveArm(){
	int count=2;
	dropArm();
	while(count){
		for(int i=110;i>80;i-=2){
			moveArm(i);
			Serial.println(arm.read());
			delay(10);
		}
		for(int i=80;i<110;i+=2){
			moveArm(i);
			delay(10);
		}
		count--;
	}

}
void FARO_Robot::moveArm(int angle){
	armPosition=2;
	arm.write(angle);
}


/**************************************************

LDR

**********************************************/

void FARO_Robot::calibrateLight(){
	//delay(1000);
	LDR_thresholdL=analogRead(LDR_L);
	LDR_thresholdR=analogRead(LDR_R);
}

void FARO_Robot::LDR_getValues(){
	LDR_sensL=analogRead(LDR_L);
	LDR_sensR=analogRead(LDR_R);
	//Serial.print(LDR_sensL);
	//Serial.print("    ");
	//Serial.println(LDR_sensR);
}

void FARO_Robot::followLight(){
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


void FARO_Robot::escapeLight(){
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


void FARO_Robot::sayHi(int LDRsensitivity, int number){
	if(abs(analogRead(LDR_L)-oldValue_LDR)>=LDRsensitivity){
		counter_sayHi++;
		if(counter_sayHi>=number){
			waveArm();
			counter_sayHi=0; 
		}
	}
	oldValue_LDR=analogRead(LDR_L);

}

/********************************************

sound

********************************************/

void FARO_Robot::startRandomRun(){
	randomfillArray();
	runTimer=millis();
	arrayPoint=0;
	changeSpeed(255);
	runFlag=true;

}

void FARO_Robot::stopRandomRun(){
	runFlag=false;
}
void FARO_Robot::randomfillArray(){
	direction[0]=random(4)+1;
	timeSpan[0]=0;
	for(int i=1;i<100;i++){
		direction[i]=random(4)+1;
		timeSpan[i]=random(100,1000);
	}
}


void FARO_Robot::run(){
	if(runFlag){
		if(millis()-runTimer>=timeSpan[arrayPoint]*powerFactor*sizeFactor){

			arrayPoint++;
			stop();
			delay(10);
			changeAction();
			runTimer=millis();
			
		}
	}else{
		arrayPoint=0;
		stop();
	}
}

void FARO_Robot::changeAction(){
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
		case 255:
			runFlag=false;
			stop();
		break;
	}

}


/*****************************************************


Write Names


*****************************************************/
void FARO_Robot::writingIni(){
	Serial.begin(9600); 
	digitalWrite(ledPin,HIGH);
}

void FARO_Robot::writeWithPen(int no){
	//mc.ini(12);
	writingRobot_operationFlag=0;
	writingRobot_menu(no);
	
	writingRobot_operate();
}

void FARO_Robot::writingRobot_menu(int no){
	//mc.begin();
	if(no%2){
		writingRobot_inputMode_enter();
	}else{
		writingRobot_runMode_enter();
	}
	/*while(true){
		if(digitalRead(button1)==HIGH){
			writingRobot_inputMode_enter();
			break;
		}else if(digitalRead(button2)==HIGH){
			writingRobot_runMode_enter();
			break;
		}
	} */
	digitalWrite(ledPin,LOW);
	delay(1000);
}

void FARO_Robot::writingRobot_inputMode_enter(){
	writingRobot_operationFlag=1;
}
void FARO_Robot::writingRobot_runMode_enter(){
	writingRobot_operationFlag=2;
}


void FARO_Robot::writingRobot_operate(){
	if(writingRobot_operationFlag==1){

		for(int i=0;i<3;i++){
			digitalWrite(ledPin,HIGH);
			delay(200);
			digitalWrite(ledPin,LOW);
			delay(200);
		}

		writingRobot_inputMode();

	}else if(writingRobot_operationFlag==2){
		
		for(int i=0;i<2;i++){
			digitalWrite(ledPin,HIGH);
			delay(1000);
			digitalWrite(ledPin,LOW);
			delay(1000);
			digitalWrite(ledPin,HIGH);
			delay(100);
			digitalWrite(ledPin,LOW);
			delay(100);
		}

		writingRobot_runMode();
   
	} 
}

void FARO_Robot::writingRobot_inputMode(){
  //iniSerial();
	
	Serial.flush();


  //sycronize();
	while(true){
		Serial.write(1);
		if(Serial.available()){
			//Serial.println();
			unsigned char res=Serial.read(); 
 			if(res==2){
				Serial.flush();
				break;
			}
		}
		delay(10); 
	}
   
   
  //clearEPROM();
	for(int i=0;i<512;i++){
		EEPROM.write(i,255);
	}
  
  
  //getInputs();
	int addr=0;
	while(true){
		if(Serial.available()){
			int value=Serial.read();
			if(value!=255){
				EEPROM.write(addr,value);
				addr++;
				
			}else{
				break;
			}
			 digitalWrite(13,LOW);
			 delay(200);
			 digitalWrite(13,HIGH);
		}
	//delay(25);
	}
  
}

void FARO_Robot::writingRobot_runMode(){
  //readEPROM();
	int n=0;	
	for(int i=0;i<512;i+=2){
		if(EEPROM.read(i)==255){
			direction[n]=255;
			break;
		}else{
			direction[n]=EEPROM.read(i);
			timeSpan[n]=EEPROM.read(i+1)*10;
			n++;
		}
	}
	

  //startRun();
	for(int i=0;i<3;i++){
		digitalWrite(ledPin,HIGH);
		delay(1000);
		digitalWrite(ledPin,LOW);
		delay(1000);
	}



	runTimer=millis();
	arrayPoint=0;
	changeSpeed(255);
	runFlag=true;

	changeAction();
	while(runFlag){
		run();
		powerFactor;
		sizeFactor;
	}
}
