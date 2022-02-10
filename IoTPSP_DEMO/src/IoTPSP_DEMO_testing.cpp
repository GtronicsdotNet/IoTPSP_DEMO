#include "IoTPSP_DEMO_testing.h"
#include "IoTPSP_DEMO_testSequence.h"
#include "IoTPSP_DEMO_POT.h"
#include "IoTPSP_DEMO_LEDs.h"
#include "IoTPSP_DEMO_ENC.h"
#include "IoTPSP_DEMO_TOUCH.h"
#include "IoTPSP_DEMO_OLED_HMI.h"

testResult testIoTPSP(tests testToBeDone) {

	testState currentState = START_TEST;
	testResult currentTestResult = TEST_DONE_OK;
	int testIndex = 0;

	Serial.println();

	if (testToBeDone == ALL) currentState = START_TEST;
	if (testToBeDone == LEDs) currentState = TEST_LEDs;
	if (testToBeDone == POT) currentState = TEST_POT;
	if (testToBeDone == TOUCH) currentState = TEST_TOUCH;
	if (testToBeDone == ENCODER) currentState = TEST_ENCODER;
	if (testToBeDone == OLED) currentState = TEST_OLED;
	if (testToBeDone == LCD) currentState = TEST_LCD;
	if (testToBeDone == RELAY) currentState = TEST_RELAY;
	if (testToBeDone == HCSR04) currentState = TEST_HCSR04;
	if (testToBeDone == DHTxx) currentState = TEST_DHTxx;
	if (testToBeDone == MIC) currentState = TEST_MIC;
	if (testToBeDone == MP3) currentState = TEST_MP3;
	if (testToBeDone == SDCARD) currentState = TEST_SDCARD;
	if (testToBeDone == RTCDS) currentState = TEST_RTCDS;
	if (testToBeDone == LDRxTC) currentState = TEST_LDRxTC;
	if (testToBeDone == MOTOR) currentState = TEST_MOTOR;
	if (testToBeDone == LEVELSHIFTER) currentState = TEST_LEVELSHIFTER;
	if (testToBeDone == DIGITALJ3J34) currentState = TEST_DIGITALJ3J34;

	//state machine
	while (currentState != TEST_DONE) {
		// here code to be execute each time that the state changes
		Serial.println();
		Serial.println("-----------------------------------");

		switch (currentState) {

		case START_TEST: //starting testing procedure
			Serial.println("Starting testing procedure...");
			Serial.println();
			//currentState = testSequence[testIndex]; //TEST_LEDs; //set next state
			break;

		case TEST_LEDs:
			currentState = setNextState(testIndex, testToBeDone, testLEDs);
			break;

		case TEST_POT:
			currentState = setNextState(testIndex, testToBeDone, testPOT);
			break;

		case TEST_TOUCH:
			currentState = setNextState(testIndex, testToBeDone, testTOUCH);
			break;

		case TEST_ENCODER:
			currentState = setNextState(testIndex, testToBeDone, testENCODER);
			break;

		case TEST_OLED:
			currentState = setNextState(testIndex, testToBeDone, testOLED);
			break;

		case TEST_LCD:
			//currentState = setNextState(testIndex, testToBeDone, testLCD);
			break;

		case TEST_RELAY:
			//currentState = setNextState(testIndex, testToBeDone, testRELAY);
			break;

		case TEST_HCSR04:
			//currentState = setNextState(testIndex, testToBeDone, testHCSR04);
			break;

		case TEST_DHTxx:
			//currentState = setNextState(testIndex, testToBeDone, testDHT);
			break;

		case TEST_MIC:
			//currentState = setNextState(testIndex, testToBeDone, testMIC);
			break;

		case TEST_MP3:
			//currentState = setNextState(testIndex, testToBeDone, testMP3);
			break;

		case TEST_SDCARD:
			//currentState = setNextState(testIndex, testToBeDone, testSDCARD);
			break;

		case TEST_RTCDS:
			//currentState = setNextState(testIndex, testToBeDone, testRTCDS);
			break;

		case TEST_LDRxTC:
			//currentState = setNextState(testIndex, testToBeDone, testLDR);
			break;

		case TEST_MOTOR:
			//currentState = setNextState(testIndex, testToBeDone, testMOTOR);
			break;

		case TEST_LEVELSHIFTER:
			//currentState = setNextState(testIndex, testToBeDone, testLEVELSHIFTER);
			break;

		case TEST_DIGITALJ3J34:
			//currentState = setNextState(testIndex, testToBeDone, testDIGITALJ3J34);
			break;

		case TEST_END:
			//currentState=tstDONE;
			return currentTestResult;
			break;

		case ERROR:
			//currentState=tstDONE;
			return TEST_DONE_ERROR;
			break;

		case ABORT:
			//currentState=tstDONE;
			return TEST_ABORTED;
			break;
		}

	}
}


testState setNextState(int& i, tests& testToBeDone, testTypeResult(*currentTest)()) {

	testTypeResult currentTestResult = currentTest();
	if (currentTestResult.result == TEST_ABORTED)
		return ABORT;

	if (currentTestResult.result == TEST_DONE_ERROR)
		return ERROR;


	if (currentTestResult.testType == testToBeDone)
	{
		return TEST_END;
	}
	else
	{
		if (i + 1 < sizeof(testSequence) / sizeof(int))
		{
			i++;
			return testSequence[i];
		}
		else
		{
			return TEST_END;
		}
	}
}

void restoreAllPins() {

	//Serial.print("Restoring pin: ");
	//Serial.println(p1);

	int allPins[] = {
		SERVO_GPIO,
		SPI_CS_GPIO,
		RELAY_GPIO,
		DHT_GPIO,
		TRIGGER_GPIO,
		ECHO_GPIO,
		RX_GPIO,
		TX_GPIO,
		SPEAKER_GPIO,
		SPI_SCLK_GPIO,
		GRN_LED_GPIO,
		I2C_SDA_GPIO,
		I2C_SCL_GPIO,
		RED_LED_GPIO,
		DIR_GPIO,
		STEP_GPIO,
		ENC_A_GPIO,
		TOUCH_BUTTON_GPIO,
		ENC_SW_GPIO,
		LDR_xTC_GPIO,
		ENC_B_GPIO,
		POT_GPIO,
		MIC_GPIO
	};

	for (int i = 0; i < (sizeof(allPins) / sizeof(int)); i++)
	{
		pinMode(allPins[i], INPUT);
	}
}

// check if user wants to abort current test
testResult abortCurrentTest() {

	if (Serial.available()) {
		byte read = Serial.read();
		switch (read) {
		case 'x':
			return TEST_ABORTED; //return with abort code
			break;
		}
	}
	else
	{
		return TEST_DONE_OK;
	}
}


void restoreUsedPins(int p1, int p2, int p3) {

	Serial.print("Restoring pin: ");
	Serial.println(p1);
	pinMode(p1, INPUT);

	//if (p2>=0)
	{
		Serial.print("Restoring pin: ");
		Serial.println(p2);
		pinMode(p2, INPUT);
	}

	//if (p3>=0)
	{
		Serial.print("Restoring pin: ");
		Serial.println(p3);
		pinMode(p3, INPUT);
	}
}

void restoreUsedPins(int p1, int p2) {

	Serial.print("Restoring pin: ");
	Serial.println(p1);
	pinMode(p1, INPUT);

	//if (p2 >= 0)
	{
		Serial.print("Restoring pin: ");
		Serial.println(p2);
		pinMode(p2, INPUT);
	}
}

void restoreUsedPins(int p1) {

	Serial.print("Restoring pin: ");
	Serial.println(p1);
	pinMode(p1, INPUT);
}


testResult initTest(const char* testName, bool waitOK, bool waitStart) {

	pinMode(ENC_SW_GPIO, INPUT_PULLUP);

	Serial.println("--------------------------");
	Serial.print("Testing ");
	Serial.println(testName);
	Serial.println("--------------------------");
	Serial.println();

	if (waitStart)
	{
		Serial.println("Press ENC switch to start testing");
		Serial.println("send 'x' to abort");
		Serial.println();

		delay(300);

		while (digitalRead(ENC_SW_GPIO))
		{
			if (abortCurrentTest())
				return  TEST_ABORTED;
		}
		delay(300);
	}

	Serial.print("...start testing ");
	Serial.println(testName);
	Serial.println("send 'x' to abort");
	Serial.println();

	if (waitOK)
	{
		Serial.print("press ENC switch to confirm ");
		Serial.print(testName);
		Serial.println(" OK");
		Serial.println();
	}

	return TEST_DONE_OK;
}

void printTestOK(const char* testName) {
	Serial.println();
	Serial.print(testName);
	Serial.println(" OK!");
	Serial.println();
}
