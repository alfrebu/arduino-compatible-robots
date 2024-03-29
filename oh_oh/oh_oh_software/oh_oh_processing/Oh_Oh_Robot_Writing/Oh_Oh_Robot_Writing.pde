/**********************************************************************

Working with Oh_Oh robot and the arduino sketch "Robot_Writing.pde"

don't change the data array if you don't know how it works


***********************************************************************/


import processing.serial.*;

Serial myPort;

static final float LU=20;//0.21s->8cm (lengthUnit,1 unit=8cm)
static final float RU=0.242;//0.87s->360 degrees,0.00242s->1 degree (RotationUnit)/1.07,0.00297

long timer=0;

float[][] data={
{4,26*RU,1,4.47*LU,6,10,2,4.47*LU,5,10,1,4.47*LU,3,52*RU,6,10,2,4.47*LU,5,10,3,33*RU,1,3.6*LU,3,33*RU,6,10,2,3.6*LU,5,10,7,10},//A*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,76*RU,6,10,2,4*LU,5,10,3,29*RU,1,4*LU,6,10,2,4*LU,5,10,1,4*LU,4,29*RU,6,10,2,4*LU,5,10,3,29*RU,1,4*LU,6,10,2,4*LU,5,10,7,10},//B*
{4,45*RU,1,5.65*LU,4,45*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,7,10},//C*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,64*RU,6,10,2,4.47*LU,5,10,3,52*RU,1,4.47*LU,6,10,2,4.47*LU,5,10,7,10},//D*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,90*RU,6,10,2,4*LU,5,10,3,27*RU,1,4.4*LU,4,27*RU,6,10,2,2*LU,5,10,3,34*RU,1,3.6*LU,4,34*RU,6,10,2,4*LU,5,10,7,10},//E*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,90*RU,6,10,2,4*LU,5,10,3,26*RU,1,4.47*LU,4,26*RU,6,10,2,2*LU,5,10,7,10},//F*
{4,45*RU,1,5.65*LU,4,45*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,3,135*RU,6,10,2,2.78*LU,5,10,7,10},//G*
{1,4*LU,6,10,2,4*LU,5,10,1,2*LU,3,90*RU,6,10,2,4*LU,5,10,3,90*RU,1,2*LU,6,10,2,4*LU,5,10,7,10},//H*
{1,4*LU,6,10,2,4*LU,5,10,7,10},//I*
{1,1*LU,3,64*RU,6,10,2,2.23*LU,5,10,3,126*RU,6,10,2,4*LU,5,10,7,10},//J*
{1,4*LU,6,10,2,4*LU,5,10,1,2*LU,3,64*RU,6,10,2,4.47*LU,5,10,1,4.47*LU,3,90*RU,6,10,2,4.47*LU,5,10,7,10},//K?
{1,4*LU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,7,10},//L*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,45*RU,6,10,2,2.78*LU,5,10,3,90*RU,6,10,2,2.78*LU,5,10,3,45*RU,1,4*LU,6,10,2,4*LU,5,10,7,10},//M*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,45*RU,6,10,2,5.65*LU,5,10,4,45*RU,1,4*LU,6,10,2,4*LU,5,10,7,10},//N*
{1,4*LU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,7,10},//O*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,76*RU,6,10,2,4*LU,5,10,3,29*RU,1,4*LU,6,10,2,4*LU,5,10,7,10},//P*
{4,45*RU,1,2.82*LU,3,90*RU,6,10,2,2.78*LU,5,10,4,45*RU,1,4*LU,6,10,2,4*LU,5,10,4,90*RU,6,10,2,4*LU,5,10,4,90*RU,6,10,2,4*LU,5,10,4,90*RU,6,10,2,4*LU,5,10,7,10},//Q*
{1,4*LU,6,10,2,4*LU,5,10,1,4*LU,3,76*RU,6,10,2,4*LU,5,10,3,29*RU,1,4*LU,6,10,2,4*LU,5,10,1,4*LU,4,42*RU,6,10,2,4.47*LU,5,10,7,10},//R*
{4,45*RU,1,5.65*LU,4,45*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,2*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,4,90*RU,6,10,2,2*LU,5,10,4,90*RU,6,10,2,4*LU,5,10,7,10},//S*
{1,4*LU,3,90*RU,6,10,2,4*LU,5,10,1,2*LU,4,90*RU,6,10,2,4*LU,5,10,7,10},//T*
{1,4*LU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,3,90*RU,6,10,2,4*LU,5,10,7,10},//U*
{1,4*LU,3,26*RU,6,10,2,4.47*LU,5,10,3,128*RU,6,10,2,4*LU,5,10,7,10},//V*
{1,4*LU,3,14*RU,6,10,2,4.12*LU,5,10,4,39*RU,1,2.24*LU,6,10,2,2.24*LU,5,10,1,2.24*LU,3,52*RU,6,10,2,2.24*LU,5,10,4,29*RU,1,4.12*LU,6,10,2,4.12*LU,5,10,7,10},//W*
{1,4*LU,3,45*RU,6,10,2,5.65*LU,5,10,4,45*RU,1,4*LU,4,45*RU,6,10,2,5.65*LU,5,10,7,10},//X*
{1,4*LU,3,45*RU,6,10,2,2.82*LU,5,10,4,45*RU,6,10,2,2*LU,5,10,4,26*RU,1,4.47*LU,4,19*RU,6,10,2,2.82*LU,5,10,7,10},//Y*
{1,4*LU,3,90*RU,6,10,2,4*LU,5,10,3,45*RU,1,5.65*LU,6,10,2,5.65*LU,5,10,1,5.65*LU,4,45*RU,6,10,2,4*LU,5,10,7,10},//Z*

};
//1-forward,2-backward,3-left,4-right,5-liftArm,6-dropArm
void setup(){
  println(Serial.list());
  myPort=new Serial(this,Serial.list()[0],9600);
  while(true){
    if(myPort.available()>0){
      if(myPort.readChar()==1){
       println(myPort.available());
       println("success") ;
       myPort.clear();
       myPort.write(2);
       break;
      }
    }
  }
}
void draw(){

  
}
void keyPressed(){
    sendData(keyCode-65);
     println(key);

}
void sendData(int n){
  for(int i=0;i<data[n].length;i++){
   myPort.write(int(data[n][i]));
   delay(10);
  }
}
