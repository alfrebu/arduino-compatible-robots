#include "WProgram.h"
#include "MultiClick.h"

MultiClick::MultiClick()
{
}	

void MultiClick::ini(char button, int countTime)
{
	buttonPin=button;
	pinMode(button,OUTPUT);
	this->threshold=countTime;
	
	
	clicks=0;
	buttonLast=digitalRead(buttonPin);
	timer=0;

}

void MultiClick::getAClick()
{
	if(!clicks){
		iStarted=true;
	}
	timer=millis();
	clicks++;
}

void MultiClick::begin()
{
	iStarted=false;
	clicks=0;
	while(true){
		checkButton();
		if(iStarted && millis()-timer>=threshold)
		{
			
			break;
		}
	
	}
}
void MultiClick::checkButton()
{
	bool val=digitalRead(buttonPin);
	if(!val && buttonLast){
		//Serial.print("!");
		getAClick();
	}
	buttonLast=val;

}