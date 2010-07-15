#include "WProgram.h"
#include "Oh_Oh_Robot.h"
#include "../EEPROM/EEPROM.h"



#include "../Servo/Servo.h"

/*****************************************************


Write Names

example using scriptRun functions


*****************************************************/
void Oh_Oh_Robot::writingIni(){
	Serial.begin(9600); 
	digitalWrite(ledPin,HIGH);
	onOffMode();
	onOffMode();
}

void Oh_Oh_Robot::writeWithPen(int no){
	writingRobot_operationFlag=0;
	writingRobot_menu(no);
	
	writingRobot_operate();
}

void Oh_Oh_Robot::writingRobot_menu(int no){
	if(no%2){
		writingRobot_inputMode_enter();
	}else{
		writingRobot_runMode_enter();
	}
	digitalWrite(ledPin,LOW);
	delay(1000);
}

void Oh_Oh_Robot::writingRobot_inputMode_enter(){
	writingRobot_operationFlag=1;
}
void Oh_Oh_Robot::writingRobot_runMode_enter(){
	writingRobot_operationFlag=2;
}


void Oh_Oh_Robot::writingRobot_operate(){
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

void Oh_Oh_Robot::writingRobot_inputMode(){
  //iniSerial();
	
	Serial.flush();


  //sycronize();
	while(true){
		Serial.write(1);
		if(Serial.available()){
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

void Oh_Oh_Robot::writingRobot_runMode(){
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
	onOff(true);
	liftArm();
	runFlag=true;

	changeAction();
	while(runFlag){
		run();
		powerFactor;
		sizeFactor;
	}
}
