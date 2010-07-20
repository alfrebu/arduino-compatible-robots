#include "WProgram.h"
#include "Oh_Oh_Robot.h"

void Oh_Oh_Robot::funBlink(){
	for(int i=0;i<10;i++){
		digitalWrite(ledPin,HIGH);
		digitalWrite(ledPin2,LOW);
		delay(50);
		digitalWrite(ledPin,LOW);
		digitalWrite(ledPin2,HIGH);
		delay(50);
	}
	digitalWrite(ledPin,LOW);
	digitalWrite(ledPin2,LOW);

}