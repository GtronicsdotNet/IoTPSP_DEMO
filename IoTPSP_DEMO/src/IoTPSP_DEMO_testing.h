#pragma once

#include "arduino.h"
#include "IoTPSP_DEMO_pin_definition.h"



enum tests {
	ALL,
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
	LEVELSHIFTER,
	DIGITALJ3J34
};

enum testState {
	START_TEST,
	TEST_LEDs,
	TEST_POT,
	TEST_TOUCH,
	TEST_ENCODER,
	TEST_OLED,
	TEST_LCD,
	TEST_RELAY,
	TEST_HCSR04,
	TEST_DHTxx,
	TEST_MIC,
	TEST_MP3,
	TEST_END,
	TEST_DONE,
	TEST_SDCARD,
	TEST_RTCDS,
	TEST_LDRxTC,
	TEST_MOTOR,
	TEST_LEVELSHIFTER,
	TEST_DIGITALJ3J34,
	ABORT,
	ERROR
};

enum testResult {
	TEST_DONE_OK = 0,
	TEST_DONE_ERROR = 1,
	TEST_ABORTED = 2,
	TEST_RUNNING = 99
};

struct testTypeResult {
	tests testType;
	testResult result;
};



testResult testIoTPSP(tests testToBeDone);
testResult abortCurrentTest();
testState setNextState(int& i, tests& testToBeDone, testTypeResult(*currentTest)());
void restoreUsedPins(int p1);
void restoreUsedPins(int p1, int p2);
void restoreUsedPins(int p1, int p2, int p3);
void restoreAllPins();
//testResult initTest(const char* testName);
testResult initTest(const char* testName, bool waitOK = true, bool waitStart = true);
void printTestOK(const char* testName);
