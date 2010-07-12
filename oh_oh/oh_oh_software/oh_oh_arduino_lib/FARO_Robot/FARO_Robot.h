#ifndef FARO_Robot_h
#define FARO_Robot_h

#include "../Servo/Servo.h"
#include "../MultiClick/MultiClick.h"


class FARO_Robot
{

	public:
		FARO_Robot();

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


//Servo
		
		void getServo();
		
		bool armPosition; //0-drop 1-lift 2-free

		void liftArm();
		void dropArm();
		void waveArm();

	//	void moveArm(int angle);

		void sayHi(int LDRsensitivity=10,int number=6);

//Light sensing		

		void calibrateLight();
		void followLight();
		void escapeLight();

//Scriptted running
		
		
		float powerFactor;
		float sizeFactor;
		

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

		char pushButton;
		char button1;
		char button2;		
		char ledPin;

		void turnLeftWheel(int dir);
		void turnRightWheel(int dir);

//Servo

		Servo arm;

		void moveArm(int angle);

//LDR

		int oldValue_LDR;
		int counter_sayHi;

		char LDR_L;
		char LDR_R;
		void LDR_getValues();

//Scriptted running

		short direction[100];
		int timeSpan[100];
		short arrayPoint; 
		
		bool runFlag;
		long runTimer;


		void changeAction();
		void run();

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


};

#endif
