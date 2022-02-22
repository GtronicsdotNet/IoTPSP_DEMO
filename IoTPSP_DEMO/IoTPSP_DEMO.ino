/*
 Name:		IoTPSP_DEMO.ino
 Created:	09-Feb-22 19:28:55
 Author:	gtronics
*/


#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include <Wire.h>
#include "src\IoTPSP_DEMO_pin_definition.h"
#include "src\IoTPSP_DEMO_serial_HMI.h"
#include "src\IoTPSP_DEMO_testing.h"
#include "src\IoTPSP_DEMO_OLED_HMI.h"
#include "src\Bounce2.h"
#include "src\IoTPSP_DEMO_POT.h"
#include "src\IoTPSP_DEMO_TOUCH.h"
#include "src\IoTPSP_DEMO_LEDs.h"
#include "src\IoTPSP_DEMO_RTC.h"
#include "src\IoTPSP_DEMO_RELAY.h"
#include "src\IoTPSP_DEMO_HCSR04.h"
#include "src\IoTPSP_DEMO_DHT.h"
#include "src\IoTPSP_DEMO_MIC.h"
#include "src\IoTPSP_DEMO_MP3.h"

SSD1306Wire display(0x3c, I2C_SDA_GPIO, I2C_SCL_GPIO);  //display(address, SDA, SCL)

OledHmi ui(&display);
int encoderPosition = 0;
//int lastEncoderPosition = 0;
bool firstRun = true;
bool runDemo = false;
bool encoderLastA = LOW;
bool currentEncA = LOW;
DemoMenu mainMenu;
tests demoSelection;
unsigned long lastEncChange = 0;
Button encoderSwitch(ENC_SW_GPIO, 25);
int encoderSelection = 0;
int encoderDirection = 0;
//bool encoderArmed = true;

#define USE_INTERRUPTS	// comment this line to disable interrupts on A and B encoder channels 
						// and use simple encoder signal handling

// the setup function runs once when you press reset or power the board
void setup() {
	bool proceed = false;
	unsigned long lastDisplayToggle = 0;
	bool displayLastRow = true;

	//setup encoder pins
	pinMode(ENC_A_GPIO, INPUT_PULLUP);
	pinMode(ENC_B_GPIO, INPUT_PULLUP);

#ifdef USE_INTERRUPTS
	//attachInterrupt(digitalPinToInterrupt(ENC_A_GPIO), handleEncoderAchange, FALLING); //CHANGE
	attachInterrupt(digitalPinToInterrupt(ENC_B_GPIO), handleEncoderBchange, RISING);
#endif

	Serial.begin(115200);
	Serial.println();
	Serial.println("-----------------------");
	Serial.println("- IoTPSP DEMO program -");
	Serial.println("-----------------------");
	Serial.println();
	printSerialHMI();
	Serial.println();

	ui.init();
	

	while (!proceed)
	{
		if (millis() - lastDisplayToggle > 750)
		{
			ui.displayWelcomeScreen(displayLastRow);
			displayLastRow = !displayLastRow;
			lastDisplayToggle = millis();
		}

		encoderSwitch.update();
		if (encoderSwitch.isRising())
			proceed = true;
	}

	//delay(500);
	encoderPosition = 0;
}


// the loop function runs over and over again until power down or reset
void loop() {


	if (Serial.available()) {
		byte read = Serial.read();
		if (read != 0xD) {
			//runDemo = true;
			switch (read) {
				
			case 'p':
				testPOT(&ui, &encoderSwitch);
				break;

			case 'l':
				testLEDs(&ui, &encoderSwitch);
				break;

			case 't':
				testTOUCH(&ui, &encoderSwitch);
				break;

			case 'z':
				testRTCDS(&ui, &encoderSwitch);
				break;

			case 'r':
				testRELAY(&ui, &encoderSwitch);
				break;

			case 'h':
				testHCSR04(&ui, &encoderSwitch);
				break;

			case 'd':
				testDHT(&ui, &encoderSwitch);
				break;

			case 'm':
				testMIC(&ui, &encoderSwitch);
				break;

			case 'y':
				testMP3(&ui, &encoderSwitch);
				break;

			//case 's':
			//	//testSDCARD
			//	break;
			//
			//case 'n':
			//	//testLDR
			//	break;
			//
			//case 'w':
			//	//testMOTOR
			//	break;

			default:
				Serial.println();
				Serial.print("WRONG SELECTION, to start testing ");
				printSerialHMI();
				break;

			}

			Serial.flush();
			Serial.println();
			Serial.println();
		}
	}
	
#ifndef USE_INTERRUPTS
	currentEncA = digitalRead(ENC_A_GPIO);
	if ((encoderLastA == LOW) && (currentEncA == HIGH))
	{
		if (digitalRead(ENC_B_GPIO) == LOW) {
			encoderPosition++;
		}
		else {
			encoderPosition--;
		}
		lastEncChange = millis();
	}
	encoderLastA = currentEncA;
	encoderSelection = encoderPosition;
#endif

#ifdef USE_INTERRUPTS
	if (millis() - lastEncChange > 200) {
		encoderSelection += encoderDirection;
		encoderDirection = 0;
		lastEncChange = millis();
	}


#endif

	//if (encoderPosition != lastEncoderPosition)
	//{
	//	if (encoderPosition - lastEncoderPosition > 1)
	//	{
	//		encoderPosition = lastEncoderPosition +1;
	//	}
	//		
	//	if (encoderPosition - lastEncoderPosition < -1) 
	//	{
	//		encoderPosition = lastEncoderPosition - 1;
	//	}
	//	Serial.println(encoderPosition);
	//	lastEncoderPosition = encoderPosition;
	//}
	//Serial.println(encoderSelection);

	if (encoderSelection < 0)
		encoderSelection = 0;

	if (encoderSelection > mainMenu.getMenuItemsN() - 1)
		encoderSelection = mainMenu.getMenuItemsN() - 1;

	if (firstRun)
		encoderSelection = 0;

	firstRun = false;

	ui.displaySelectionScreen(encoderSelection);

	encoderSwitch.update();
	if (encoderSwitch.isRising())
	{
		demoSelection = mainMenu.getMenuItem(encoderSelection);
		runDemo = true;
	}

	if (runDemo) {
		if (demoSelection == LEDs) testLEDs(&ui, &encoderSwitch);
		if (demoSelection == POT) testPOT(&ui, &encoderSwitch);
		if (demoSelection == TOUCH) testTOUCH(&ui, &encoderSwitch);
		if (demoSelection == RTCDS) testRTCDS(&ui, &encoderSwitch);
		if (demoSelection == RELAY) testRELAY(&ui, &encoderSwitch);
		if (demoSelection == HCSR04) testHCSR04(&ui, &encoderSwitch);
		if (demoSelection == DHTxx) testDHT(&ui, &encoderSwitch);
		if (demoSelection == MIC) testMIC(&ui, &encoderSwitch);
		if (demoSelection == MP3) testMP3(&ui, &encoderSwitch);

		runDemo = false;
	}


}


void handleEncoderAchange() {
	bool encB = digitalRead(ENC_B_GPIO);
	bool encA = digitalRead(ENC_A_GPIO);

	{
		if (encA == HIGH)
		{
			if (encB == LOW)
			{
				encoderPosition++;
				encoderDirection = 1;
			}
			else
			{
				encoderPosition--;
				encoderDirection = -1;
			}
		}
		else
		{
			if (encB == HIGH)
			{
				encoderPosition++;
				encoderDirection = 1;
			}
			else
			{
				encoderPosition--;
				encoderDirection = -1;
			}
		}

		if (encoderPosition < 0)
			encoderPosition = 0;

		if (encoderPosition > mainMenu.getMenuItemsN() - 1)
			encoderPosition = mainMenu.getMenuItemsN() - 1;

	}
}


void handleEncoderBchange() {

	bool encB = digitalRead(ENC_B_GPIO);
	bool encA = digitalRead(ENC_A_GPIO);

	{
		if (encB == HIGH)
		{
			if (encA == HIGH)
			{
				encoderPosition++;
				encoderDirection = 1;
			}
			else
			{
				encoderPosition--;
				encoderDirection = -1;
			}
		}
		else
		{
			if (encA == LOW)
			{
				encoderPosition++;
				encoderDirection = 1;
			}
			else
			{
				encoderPosition--;
				encoderDirection = -1;
			}
		}

		if (encoderPosition < 0)
			encoderPosition = 0;

		if (encoderPosition > mainMenu.getMenuItemsN() - 1)
			encoderPosition = mainMenu.getMenuItemsN() - 1;

	}
}



