#ifndef Oh_Oh_Robot_h
#define Oh_Oh_Robot_h

#include "../Servo/Servo.h"

#define LENGTH_IR 30

class Oh_Oh_Robot
{

	public:
		Oh_Oh_Robot();

		int speedL; 
		int speedR;
		int situation; //1-forward 2-backward 3-left 4-right 0-stop
		
		int LDR_sensL;
		int LDR_sensR;
		int LDR_thresholdL;
		int LDR_thresholdR;


		

		void forward();
		void backward();
		void left();
		void right();
		void stop();

		void changeSpeed(int spd, int wheel=3);
		void onOff(bool flag,int wheel=3);
		void onOffMode();
		// onOff mode: change speed without using PWM, only on/off(HIGH/LOW)

		
//Servo
		
		void getServo(int n=11);
		
		bool armPosition; //0-drop 1-lift 2-free

		void liftArm();
		void dropArm();
		void waveArm();
		void moveArmSlow();

		void presetArm(int dropAngle, int liftAngle);


		void sayHi(int LDRsensitivity=30,int number=6);
		//para1: change the sensitivity of LDR;para2: how many countings it needs for robot to wave

//Light sensing		

		void calibrateLight();
		void followLight();
		void escapeLight();

//Infrared

		void iniIR(char pin=19,int A_1=0x490,int A_2=0xC90,int B_1=0x090,int B_2=0x890,int C=0xA90,int D=0x290);
		void runIR();

//Scriptted running
		
		
		float powerFactor;
		float sizeFactor;
		
		void run(int span=1000);
		
	//random run

		void startRandomRun();
		void stopRandomRun();
	

	//write names
		void writingIni();
		void writeWithPen(int no);


/************************************************


private


*************************************************/

	private:
		char motor_1_1;
		char motor_1_2;
		char motor_1_PWM;
		char motor_2_1;
		char motor_2_2;
		char motor_2_PWM;

		char button;
		char ledPin;
		char ledPin2;

		void turnLeftWheel(int dir);
		void turnRightWheel(int dir);

//Servo

		Servo arm;
		int dropAngle;
		int liftAngle;
		int servoDirection;
		int timerServo;
		
		void moveArm(int angle);
//LDR

		int oldValue_LDR;
		int counter_sayHi;

		char LDR_L;
		char LDR_R;
		void LDR_getValues();
		
//Infrared
		
		int A_1;
		int A_2;
		int B_1;
		int B_2;
		int C;
		int D;
		
		char pinIR;
		int valueIR;
		bool modeIR;
		long timerIR;
		
		void setValue(int val);
		void switchModeIR();
		void funFunction();
		int getIRSignal();

//Scriptted running

		short direction[100];
		int timeSpan[100];
		short arrayPoint; 
		
		bool runFlag;
		long runTimer;


		void changeAction();

	//Write names
		
		//MultiClick mc;
		
		int writingRobot_operationFlag;
		void writingRobot_menu(int no);

		void writingRobot_inputMode_enter();
		void writingRobot_runMode_enter();

		void writingRobot_operate();

		void writingRobot_inputMode();
		void writingRobot_runMode();

	//Random run

		void randomfillArray();

	//leds
		void funBlink();
};

#endif
