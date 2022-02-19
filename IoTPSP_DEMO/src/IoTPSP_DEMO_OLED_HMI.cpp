//
//
//

#include "IoTPSP_DEMO_OLED_HMI.h"
#include "IoTPSP_DEMO_board_definition.h"
//#include "arduino.h"


#ifdef TEST_ARDUINO_NANO
	//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
//#include "OLEDDisplayUi.h"
#endif



OledHmi::OledHmi(OLEDDisplay* display) {
	this->m_display = display;
}

void OledHmi::init() {
	this->m_display->init();
	this->m_display->flipScreenVertically();
	this->m_RowPositionPix = 0;
	this->m_currentRowIndex = 0;
}

void OledHmi::initRowPositionPix(int firstRowPix, int incrementPix) {
	this->m_RowPositionPix = 0;
	this->m_currentRowIndex = 0;
	this->m_firstRowPix = firstRowPix;
	this->m_incrementPix = incrementPix;
}

void OledHmi::setRowPositionPix(int offsetPix) {
	this->m_RowPositionPix = m_firstRowPix + m_incrementPix * m_currentRowIndex + offsetPix;
	this->m_currentRowIndex++;
}


int OledHmi::getRowPositionPix() {
	return this->m_RowPositionPix;
}

void OledHmi::displayWelcomeScreen(bool displayLastRow) {

	constexpr int leftIndentPix = 0;
	constexpr int firstRowPix = 0;
	constexpr int lastRowPix = 53;
	constexpr int incRowPix = 10;

	this->initRowPositionPix(firstRowPix, incRowPix);

	this->m_display->clear();
	this->m_display->setTextAlignment(TEXT_ALIGN_LEFT); //TEXT_ALIGN_CENTER
	this->m_display->setFont(ArialMT_Plain_10);

	this->setRowPositionPix();
	this->m_display->drawString(leftIndentPix + 23, this->getRowPositionPix(), "GtronicsShop.com");

	this->setRowPositionPix();
	this->m_display->drawString(leftIndentPix + 36, this->getRowPositionPix(), "Gtronics.NET");

	this->setRowPositionPix(1);
	this->m_display->drawString(leftIndentPix + 40 , this->getRowPositionPix(), "HI DAVE!");

	this->setRowPositionPix();
	this->m_display->drawString(leftIndentPix + 10, this->getRowPositionPix(), "Thanks for testing the");

	this->setRowPositionPix(1);
	this->m_display->drawString(leftIndentPix + 0, this->getRowPositionPix(), "IoT PROTO SHIELD PLUS!");

	if (displayLastRow)
		this->m_display->drawString(leftIndentPix + 5, lastRowPix, "press ENC switch to start");

	this->m_display->display();
}


void OledHmi::displayDemoScreen(const char* title, const char* description, String value, const char* instruction) {
	constexpr int leftIndentPix = 0;
	constexpr int firstRowPix = 0;
	constexpr int lastRowPix = 53;
	constexpr int incRowPix = 12;
	
	this->initRowPositionPix(firstRowPix, incRowPix);

	
	this->m_display->clear();
	this->m_display->setTextAlignment(TEXT_ALIGN_LEFT); //TEXT_ALIGN_CENTER
	this->m_display->setFont(ArialMT_Plain_10);
	
	this->setRowPositionPix();
	this->m_display->drawString(leftIndentPix, this->getRowPositionPix(), String(title));
	
	
	if (instruction)
	{
		this->setRowPositionPix();
		this->m_display->drawString(leftIndentPix, this->getRowPositionPix(), instruction);
	}
	
	this->setRowPositionPix(2);
	this->m_display->drawString(leftIndentPix, this->getRowPositionPix(), String(description));
	
	this->setRowPositionPix();
	this->m_display->drawString(leftIndentPix, this->getRowPositionPix(), value);


	this->m_display->drawString(leftIndentPix, lastRowPix, "press ENC switch to exit");

	this->m_display->display();
}

void OledHmi::displaySelectionScreen(int selection) {
	DemoMenu menu;
	constexpr int leftIndent = 10;
	constexpr int firstRow = 22;
	constexpr int incRow = 10;
	constexpr int listLenght = 3;

	this->m_display->clear();
	this->m_display->setTextAlignment(TEXT_ALIGN_LEFT); //TEXT_ALIGN_CENTER

	//display selection number
	//this->m_display->setFont(ArialMT_Plain_16);
	//this->m_display->drawString(0, 0, String(selection));

	//display instructions
	this->m_display->setFont(ArialMT_Plain_10);
	this->m_display->drawString(0, 0, "Rotate encoder to scroll");
	this->m_display->drawString(0, 10, "click to select the DEMO");

	//Display list
	this->m_display->setFont(ArialMT_Plain_10);

	//get first item
	int firstItem = selection - listLenght + 1;
	if (firstItem < 0)
		firstItem = 0;

	int lastItem = firstItem + listLenght - 1;

	for (int i = 0; i < listLenght; i++)
	{
		this->m_display->drawString(leftIndent, firstRow+incRow*i, String(menu.getMenuItemString(i+firstItem)));
	}

	// display selection
	int markerRow = selection;
	if (markerRow > listLenght - 1)
		markerRow = listLenght - 1;

	//this->m_display->drawString(0, firstRow + incRow * markerRow, String(selection));
	this->m_display->drawString(0, firstRow + incRow * markerRow, ">");



	this->m_display->display();
}



