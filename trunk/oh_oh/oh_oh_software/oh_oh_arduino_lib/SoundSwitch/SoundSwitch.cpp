#include "WProgram.h"
#include "SoundSwitch.h"

SoundSwitch::SoundSwitch(int sensorPin,int diff)
{
	pin=sensorPin;
	threshold=diff;
	oldValue=analogRead(pin);
	counter=0;	
	isOn=false;
	isTurnningOn=false;
	isTurnningOff=false;
}
void SoundSwitch::setThreshold(int diff){
	threshold=diff;
}
void SoundSwitch::checkState()
{

	int value=analogRead(pin);
	int diff=abs(value-oldValue);
	oldValue=value;
	if(diff>threshold){

		counter=10;
		if(isOn==false){
			isOn=true;
			
			isTurnningOn=true;
		}else{
			isTurnningOn=false;
		}
		
	}else{
	
		if(counter-->0){
		isTurnningOn=false;

		}else{
			if(isOn==true){

				isOn=false;
				isTurnningOff=true;
			}else{

				isTurnningOff=false;
			}
			
		}
	}
};