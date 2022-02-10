// 
// 
// 

#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_LEDs.h"


//**************** test LEDs **********************
constexpr int nTimes = 10; //n times to blink leds

testTypeResult testLEDs() {
	//init D11 D12 D13
	constexpr tests testType = LEDs;

	pinMode(GRN_LED_GPIO, OUTPUT);
	pinMode(RED_LED_GPIO, OUTPUT);
	//pinMode(13, INPUT);

	int i = 0; //counter
	int stato = 0; //define state machine

	Serial.print("Testing LEDs: send x to stop");
	Serial.println();
	while (i < nTimes) {

		if (abortCurrentTest()) {
			restoreUsedPins(GRN_LED_GPIO, RED_LED_GPIO);
			return { testType, TEST_ABORTED };
		}


		switch (stato) {
		case 0:
			digitalWrite(GRN_LED_GPIO, HIGH);
			digitalWrite(RED_LED_GPIO, LOW);
			delay(100);
			stato = 1;
			break;
		case 1:
			digitalWrite(RED_LED_GPIO, HIGH);
			digitalWrite(GRN_LED_GPIO, LOW);
			delay(100);
			stato = 0;
			i = i + 1;
			break;
		}

	}
	digitalWrite(GRN_LED_GPIO, HIGH);
	digitalWrite(RED_LED_GPIO, HIGH);

	restoreUsedPins(RED_LED_GPIO, GRN_LED_GPIO);
	return { testType, TEST_DONE_OK }; //return with no error
}