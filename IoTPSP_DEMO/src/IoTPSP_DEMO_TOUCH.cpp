// 
// 
// 

#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_TOUCH.h"



//**************** test TOUCH **********************

testResult testTOUCH(OledHmi* ui, Button* encoderSwitch) {

    bool exitDemo = false;

    pinMode(TOUCH_BUTTON_GPIO, INPUT);

	const char* title = "TOUCH DEMO";
	const char* description = "TOUCH state = ";

	Serial.print(title);
	Serial.println("press ENC switch to exit");
	Serial.println("send 'x' to exit");
	Serial.println();

    while (!exitDemo) {
        //state machine
        bool currTouchState = digitalRead(TOUCH_BUTTON_GPIO); //read current touch state

		Serial.print(description);
		Serial.print(currTouchState);
		Serial.println();

		ui->displayDemoScreen(title, description, String(currTouchState));

		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if(encoderSwitch->isRising())
			exitDemo = true;

		delay(50);


    }

	restoreUsedPins(ENC_SW_GPIO, TOUCH_BUTTON_GPIO);
	return TEST_DONE_OK;
}



