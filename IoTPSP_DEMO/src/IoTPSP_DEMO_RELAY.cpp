// 
// 
// 

#include "IoTPSP_DEMO_RELAY.h"
#include "IoTPSP_DEMO_pin_definition.h"

testResult testRELAY(OledHmi* ui, Button* encoderSwitch) {

	bool exitDemo = false;

	const char* title = "RELAY DEMO";
	const char* description = "RELAY state = ";
	const char* relayState;
	const char* instruction = "TOUCH to switch RELAY";

	pinMode(RELAY_GPIO, OUTPUT);
	pinMode(TOUCH_BUTTON_GPIO, INPUT);

	Serial.println("Testing RELAY");
	Serial.println("send 'x' to abort");
	Serial.println("TOUCH to switch RELAY ON and OFF");
	Serial.println("press ENC switch to exit RELAY DEMO");
	Serial.println();


	while (!exitDemo)
	{
		bool touchState = digitalRead(TOUCH_BUTTON_GPIO);

		digitalWrite(RELAY_GPIO, touchState);

		if (touchState)
			relayState = "ON";
		else
			relayState = "OFF";

		ui->displayDemoScreen(title, description, String(relayState), instruction);


		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if (encoderSwitch->isRising())
			exitDemo = true;
	}


	restoreUsedPins(RELAY_GPIO, TOUCH_BUTTON_GPIO);
	return TEST_DONE_OK;
	
}
