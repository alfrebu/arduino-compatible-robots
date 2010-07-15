/*********************************************

testing of Oh_Oh robot's on-board microphone

calibration:
run this sketch, blowing to the microphone while
turnning the knob on board, stop turning when 
you see obvious changes in the values.


**********************************************/

void setup(){
  Serial.begin(9600);
}
void loop(){
  Serial.println(analogRead(4));
}
