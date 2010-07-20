/**********************************

Showing values from Oh_Oh robot's 
on-board LDR sensors

**********************************/
#include <IRremote.h>
#include <IRremoteInt.h>

#include <Servo.h>

#include <Oh_Oh_Robot.h>

Oh_Oh_Robot myRobot;

void setup(){
  Serial.begin(9600);
}
void loop(){
  Serial.print(analogRead(1));
  Serial.print("  ");
  Serial.println(analogRead(2));
  delay(40);
}
