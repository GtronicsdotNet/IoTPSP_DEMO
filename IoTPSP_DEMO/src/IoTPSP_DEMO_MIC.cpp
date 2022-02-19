

#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_MIC.h"

#ifdef TEST_ARDUINO_NANO
	unsigned int ad_depth = 1024;
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
	unsigned int ad_depth = 4096;
	unsigned int minMicSignalStrenght = 100;
#endif

testResult testMIC(OledHmi* ui, Button* encoderSwitch) {

	unsigned long lastMeasureMs = 0;

	unsigned int maxBarGraph = 40;

	bool exitDemo = false;
	bool measure = true;

	const char* title = "MIC MAX9814 DEMO";
	const char* description = "Signal = ";
	const char* istruction = "Make some noise!";
	const char* noMicMessage = "Check MIC connection!";

	String displayMessage = String(noMicMessage);

	constexpr int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
	unsigned int sample;

	Serial.println(title);
	Serial.println("send 'x' to abort");
	Serial.println("press ENC switch to exit MIC DEMO");
	Serial.println();

	while (!exitDemo)
	{
		
		unsigned long startMillis = millis(); // Start of sample window
		unsigned int peakToPeak = 0;   // peak-to-peak level

		unsigned int signalMax = 0;
		unsigned int signalMin = ad_depth; //4096; //1024;

		// collect data for 50 mS
		while (millis() - startMillis < sampleWindow)
		{
			sample = analogRead(MIC_GPIO);
			if (sample < ad_depth)  // toss out spurious readings
			{
				if (sample > signalMax)
				{
					signalMax = sample;  // save just the max levels
				}
				else if (sample < signalMin)
				{
					signalMin = sample;  // save just the min levels
				}
			}
		}
		peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude


		if (peakToPeak < minMicSignalStrenght)
		{
			displayMessage = String(noMicMessage);
			Serial.println(noMicMessage);
		}
		else
		{
			Serial.print("MIC detect: ");
			Serial.println(peakToPeak);

			float barGraph = ((float)maxBarGraph / (float)ad_depth) * (float)peakToPeak;

			displayMessage = String("");
			for (int i = 0; i < (int)barGraph; i++) {
				displayMessage += String("|");
			}
		}

		ui->displayDemoScreen(title, description, displayMessage, istruction);


		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if (encoderSwitch->isRising())
			exitDemo = true;
	}

	restoreUsedPins(MIC_GPIO);
	return TEST_DONE_OK;
}
