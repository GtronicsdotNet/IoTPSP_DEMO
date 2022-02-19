
#include "IoTPSP_DEMO_HCSR04.h"
#include "IoTPSP_DEMO_pin_definition.h"


testResult testHCSR04(OledHmi* ui, Button* encoderSwitch) {
	
	constexpr int maxDistance = 30;
	unsigned long pulseTimeoutus = 500000UL;// 1000000UL;
	unsigned long lastMeasureMs = 0;

	bool exitDemo = false;
	bool measure = true;

	const char* title = "HC-SR04 DEMO";
	const char* description = "Distance = ";
	const char* istruction = "Use your hand to test";
	const char* noDistanceMessage = "0 distance detected!";
	const char* tooLongDistanceMessage = "distance too long!";

	String displayMessage = String(noDistanceMessage);

	float duration;
	float cm;
	float inches;

	pinMode(TRIGGER_GPIO, OUTPUT);
	pinMode(ECHO_GPIO, INPUT);

	//delay(300);

	Serial.println("Testing HCSR04");
	Serial.println("send 'x' to abort");
	Serial.println("press ENC switch to exit HCSR04 DEMO");
	Serial.println();

	while (!exitDemo)
	{
		if (measure && millis()- lastMeasureMs > 500) {

			digitalWrite(TRIGGER_GPIO, LOW);
			delayMicroseconds(2);
			digitalWrite(TRIGGER_GPIO, HIGH);
			delayMicroseconds(10);
			digitalWrite(TRIGGER_GPIO, LOW);

			duration = pulseIn(ECHO_GPIO, HIGH, pulseTimeoutus);
			//duration = pulseIn(ECHO_GPIO, HIGH);

			// Convert the time into a distance
			cm = (duration / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
			inches = (duration / 2) / 74;   // Divide by 74 or multiply by 0.0135
			
			lastMeasureMs = millis();
		}

		if (cm > 0 && cm < maxDistance)
		{
			Serial.print("Distance - cm: ");
			Serial.println(cm);
			Serial.print(" / inches: ");
			Serial.println(inches);
			displayMessage = String(
				String(cm, 2) +
				String("cm - ") +
				String(inches, 2) +
				String("inches")
			);
			pulseTimeoutus = 1000000UL;
		}

		if (cm > maxDistance) //distance too long for this demo 
		{	
			Serial.println(tooLongDistanceMessage);
			displayMessage = String(tooLongDistanceMessage);
			pulseTimeoutus = 300000UL;
		}

		if (cm <= 0) //no distance 
		{
			Serial.println(noDistanceMessage);
			displayMessage = String(noDistanceMessage);
			pulseTimeoutus = 300000UL;
		}

		ui->displayDemoScreen(title, description, String(displayMessage), istruction);


		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if (encoderSwitch->isRising())
			exitDemo = true;

	}


	restoreUsedPins(TRIGGER_GPIO, ECHO_GPIO);
	return TEST_DONE_OK;
}