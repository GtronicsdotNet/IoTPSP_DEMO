#pragma once

#include "IoTPSP_DEMO_board_definition.h"
#include "IoTPSP_DEMO_testing.h"

#ifdef TEST_ARDUINO_NANO
	//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#endif


class OledHmi{
private:
	OLEDDisplay *m_display;

	int m_RowPositionPix;
	int m_firstRowPix;
	int m_incrementPix;
	int m_currentRowIndex;

public:
	OledHmi(OLEDDisplay* display);
	void init();
	void initRowPositionPix(int firstRowPix, int incrementPix);
	void setRowPositionPix(int offsetPix = 0);
	int getRowPositionPix();

	void displayWelcomeScreen(bool displayLastRow);

	void displaySelectionScreen(int selection);

	void displayDemoScreen(const char* title, const char* description, String value, const char* instruction = nullptr);
};





