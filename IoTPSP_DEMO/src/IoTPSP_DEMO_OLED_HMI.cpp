//
//
//

#include "IoTPSP_DEMO_board_definition.h"
//#include "arduino.h"
#include <SPI.h>
#include <Wire.h>

#ifdef TEST_ARDUINO_NANO
	//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
//#include "OLEDDisplayUi.h"
#endif

#include "IoTPSP_DEMO_OLED_HMI.h"

#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

testTypeResult testOLED() {

	constexpr tests testType = OLED;
	const char* testName = "OLED";

	pinMode(ENC_SW_GPIO, INPUT_PULLUP);

	if (initTest(testName) == TEST_ABORTED)
		return { testType, TEST_ABORTED };

#ifdef TEST_ARDUINO_NANO
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

	// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c))  // Address 0x3c for 128x64
	{
		Serial.println("SSD1306 allocation failed");
		Serial.println();

		return { testType, TEST_DONE_ERROR };
	}
	else
	{
		// init done

		// Clear the buffer.
		display.clearDisplay();

		// text display tests
		display.setTextSize(2);
		display.setTextColor(WHITE);


		for (int i; i < 10; i++) {

			display.setCursor(0, 0);
			display.println("Gtronics");
			display.println();
			display.println(i);
			display.display();
			delay(30);

			display.clearDisplay();
			display.display();
			delay(30);
		}

		display.setCursor(0, 0);
		display.println("Gtronics");
		display.println();
		display.println("OLED OK!");
		display.display();
	}

#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
	SSD1306Wire display(0x3c, I2C_SDA_GPIO, I2C_SCL_GPIO);  //display(address, SDA, SCL)

	display.init();

	display.flipScreenVertically();
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_24);

	display.clear();

	for (int i = 0; i < 10; i++) {
		display.clear();
		display.drawString(0, 0, "Gtronics");
		display.drawString(0, 25, String(i));
		display.display();
		delay(100);
	}

	display.clear();
	display.drawString(0, 0, "Gtronics");
	display.drawString(0, 25, "OLED OK!");
	display.display();

#endif

	while (digitalRead(ENC_SW_GPIO))
	{
		if (abortCurrentTest())
			return { testType, TEST_ABORTED };
	}


	printTestOK(testName);

	return { testType, TEST_DONE_OK };


}