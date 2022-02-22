#include "IoTPSP_DEMO_board_definition.h"
#include "IoTPSP_DEMO_MP3.h"
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

testResult testMP3(OledHmi* ui, Button* encoderSwitch) {

	bool exitDemo = false;
	bool mp3moduleOk = true;
	int currentFileNumber = 1;
	constexpr int nFiles = 3;

	const char* title = "MP3 PLAYER DEMO";
	const char* description = "Playing mp3 file number ";
	const char* istruction = "";
	const char* noPlayerMessage = "Check PLAYER connection!";
	const char* noSdCardMessage = "Check SD-CARD!";

	Serial.println("Testing MP3");
	Serial.println("send 'x' to abort");
	Serial.println("press ENC switch to exit MP3 DEMO");
	Serial.println();

	DFRobotDFPlayerMini myDFPlayer;

#ifdef TEST_ARDUINO_NANO
	Serial1.begin(9600); //start additional serial port to communicate with DFPlayer Mini MP3 if using NANO
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
	Serial2.begin(9600); //start additional serial port to communicate with DFPlayer Mini MP3 if using ESP32
#endif

	Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");

#ifdef TEST_ARDUINO_NANO
	if (!myDFPlayer.begin(Serial1))
#endif
#ifdef TEST_WEMOS_D1_MINI_ESP32
		if (!myDFPlayer.begin(Serial2))
#endif
	{  //Use softwareSerial to communicate with mp3.
		Serial.println("Unable to begin:");
		Serial.println("1.Please recheck the connection!");
		Serial.println("2.Please insert the SD card!");

		ui->displayDemoScreen(title, noPlayerMessage, String(noSdCardMessage), " ");

		mp3moduleOk = false;
	}

	if (mp3moduleOk) {
		Serial.println("DFPlayer Mini MP3 online.");

		myDFPlayer.volume(20);  //Set volume value. From 0 to 30
		myDFPlayer.play(currentFileNumber);  //Play the first mp3
	}

	while (!exitDemo)
	{
		if (mp3moduleOk) {
			static unsigned long timer = millis();

			if (millis() - timer > 4000)
			{
				timer = millis();
				currentFileNumber++;
				if (currentFileNumber > nFiles)
					currentFileNumber = 1;
				myDFPlayer.play(currentFileNumber);
				//myDFPlayer.next();  //Play next mp3 every 3 second.

			}

			ui->displayDemoScreen(title, description, String(currentFileNumber));
		}

		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if (encoderSwitch->isRising())
			exitDemo = true;

	}

	return TEST_DONE_OK;

}
