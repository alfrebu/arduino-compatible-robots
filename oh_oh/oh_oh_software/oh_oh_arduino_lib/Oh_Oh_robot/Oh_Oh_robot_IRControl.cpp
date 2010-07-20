#include "WProgram.h"
#include "Oh_Oh_Robot.h"

void Oh_Oh_Robot::iniIR(char pin,int A_1,int A_2,int B_1,int B_2,int C,int D){
	this->A_1=A_1;
	this->A_2=A_2;
	this->B_1=B_1;
	this->B_2=B_2;
	this->C=C;
	this->D=D;
	
	this->pinIR=pin;
	
	this->modeIR=false;
	this->timerIR=0;
	
	Serial.println("ir ready");
}

void Oh_Oh_Robot::runIR(){
	int res=getIRSignal();
	if (res) {
		if(res==A_1){
			setValue(1);
		}else if(res==A_2){
			setValue(2);
		}else if(res==B_1){
			setValue(3);
		}else if(res==B_2){
			setValue(4);
		}else if(res==C){
			setValue(5);
		}else if(res==D){
			setValue(6);
		}
	
		//Serial.println(res, HEX);
		timerIR=millis();
	}else{
		if(millis()-timerIR>=100){
			setValue(0);
		}
	}
}
void Oh_Oh_Robot::setValue(int val){

	if(valueIR!=val){
		//Serial.println(val);

		valueIR=val;
		stop();
		servoDirection=0;
		switch(valueIR){
			case 1:
				forward();
			break;
			case 2:
				backward();
			break;
			case 3:
				if(!modeIR){
					left();
				}else{
					servoDirection=1;
				}
			break;
			case 4:
				if(!modeIR){
					right();
				}else{
					servoDirection=-1;
				}
			break;
			case 5:
				funFunction();
			break;
			case 6:
				switchModeIR();
			break;
			case 0:
			
			break;
			
		}
	}
}

void Oh_Oh_Robot::switchModeIR(){
	modeIR=!modeIR;
}

void Oh_Oh_Robot::funFunction(){
	int rdm=random(0,4);
	switch(rdm){
		case 0:
			//Serial.println("0");
			waveArm();
			break;
		case 1:
			//Serial.println("1");
			funBlink();
			break;
		case 2:
			//Serial.println("2");
			left();
			delay(1000);
			break;
		case 3:
			//Serial.println("2");
			right();
			delay(1000);
			break;
	}
}

int Oh_Oh_Robot::getIRSignal(){
	int array[LENGTH_IR];
	bool flag=false;
	int bitPosition=11;
	int code=0;
	
	for(int i=0;i<LENGTH_IR;i++){
		int b=pulseIn(19,LOW,1000);
		array[i]=b;
	}
	for(int j=0;j<LENGTH_IR;j++){
		// Serial.println(array[j]);
		if(flag && bitPosition>=0 && array[j] && array[j]<2000){
			code+=(array[j]/600-1)<<bitPosition;
			bitPosition--;
		}else if(bitPosition<0){
			flag=false;
			break;
		}else{
			flag=false;
			code=0;
		}
      
		if(array[j]>2000){
			flag=true;
			bitPosition=11;
		}
		array[j]=0;

	}
	return code;

}