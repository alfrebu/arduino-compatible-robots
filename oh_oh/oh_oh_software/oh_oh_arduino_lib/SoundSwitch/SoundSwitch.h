#ifndef SoundSwitch_h
#define SoundSwitch_h


class SoundSwitch
{
	public:
		SoundSwitch(int sensorPin,int diff=100);
		void checkState();
		void setThreshold(int diff=100);
		
		bool isOn;
		bool isTurnningOn;
		bool isTurnningOff;

		int threshold;


	private:
		int pin;
		int oldValue;

		int counter;

};

#endif