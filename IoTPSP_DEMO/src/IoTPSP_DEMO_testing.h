#pragma once
#include "Bounce2.h"

enum tests {
	LEDs,
	TOUCH,
	ENCODER,
	OLED,
	LCD,
	POT,
	RELAY,
	HCSR04,
	DHTxx,
	MIC,
	MP3,
	SDCARD,
	RTCDS,
	LDRxTC,
	MOTOR,
	SERVO
};

enum testResult {
	TEST_DONE_OK = 0,
	TEST_DONE_ERROR = 1,
	TEST_ABORTED = 2,
	TEST_RUNNING = 99
};


constexpr int nItems = 9;
class DemoMenu {
private:

	//DemoMenuItem items[] = { {LEDs, "LEDs"}};
	
	tests menuItems[nItems] = { 
		LEDs, 
		TOUCH, 
		POT,
		RTCDS,
		RELAY,
		HCSR04,
		DHTxx,
		MIC,
		MP3
		//LDRxTC,
		//SDCARD,
		//SERVO,
		//MOTOR
	};

	const char* menuItemsStr[nItems] = {
		"1 - LEDs",
		"2 - TOUCH",
		"3 - POT",
		"4 - RTC",
		"5 - RELAY",
		"6 - HC-SR04",
		"7 - DHT22",
		"8 - MIC MAX9814",
		"9 - MP3 PLAYER"
		//"LDR/xTC",
		//"SDCARD",
		//"SERVO",
		//"MOTOR"
	};
	
public:
	tests getMenuItem(int index);
	int getMenuItemsN();
	const char* getMenuItemString(int index);

};

class Button {
private:
	int m_btnGpio;
	Bounce m_button;

public:
	Button(int btnGpio, int debounceInterval);
	void update();
	bool isRising();
	bool isFalling();
	bool state();
};

testResult abortCurrentTest();
void restoreUsedPins(int p1);
void restoreUsedPins(int p1, int p2);
void restoreUsedPins(int p1, int p2, int p3);
void restoreAllPins();
void initTest(const char* testName);




