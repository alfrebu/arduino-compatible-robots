#ifndef MultiClick_h
#define MultiClick_h

class MultiClick
{
	public:
		MultiClick();
		void ini(char button, int countTime=1000);
		void begin();
		int clicks;
		
	private:
		long timer;
		bool buttonLast;
		int threshold;
		bool iStarted;
		
		char buttonPin;
		
		void getAClick();
		void checkButton();
};

#endif