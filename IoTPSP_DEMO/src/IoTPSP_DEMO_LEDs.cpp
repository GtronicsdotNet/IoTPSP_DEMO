// 
// 
// 

#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_LEDs.h"


//**************** test LEDs **********************

testResult testLEDs(OledHmi* ui, Button* encoderSwitch) {

	bool exitDemo = false;
	constexpr int dly = 400;
	unsigned long lstMillis = millis();
	pinMode(GRN_LED_GPIO, OUTPUT);
	pinMode(RED_LED_GPIO, OUTPUT);
	pinMode(ENC_SW_GPIO, INPUT_PULLUP);

	const char* title = "LEDs DEMO";
	const char* description = "LED = ";

	Serial.print(title);
	Serial.println("press ENC switch to exit");
	Serial.println("send 'x' to exit");
	Serial.println();


	int state = 0; //define state machine

	while (!exitDemo) {
		unsigned long elapsed = millis() - lstMillis;
		if (elapsed>dly)
		{
			lstMillis = millis();
			if (state == 0)
				state = 1;
			else
				state = 0;
		}

		switch (state) {
		case 0:
			digitalWrite(GRN_LED_GPIO, HIGH);
			digitalWrite(RED_LED_GPIO, LOW);
			ui->displayDemoScreen(title, description, String("GREEN"));
			break;
		case 1:
			digitalWrite(RED_LED_GPIO, HIGH);
			digitalWrite(GRN_LED_GPIO, LOW);
			ui->displayDemoScreen(title, description, String("RED"));
			break;
		}

		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if (encoderSwitch->isRising())
			exitDemo = true;

	}
	digitalWrite(GRN_LED_GPIO, LOW);
	digitalWrite(RED_LED_GPIO, LOW);

	restoreUsedPins(RED_LED_GPIO, GRN_LED_GPIO);
	return TEST_DONE_OK; //return with no error
}