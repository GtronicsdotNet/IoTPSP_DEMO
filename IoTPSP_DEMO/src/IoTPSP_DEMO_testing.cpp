#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_testing.h"
#include "Bounce2.h"


void restoreAllPins() {

	//Serial.print("Restoring pin: ");
	//Serial.println(p1);

	int allPins[] = {
		SERVO_GPIO,
		SPI_CS_GPIO,
		RELAY_GPIO,
		DHT_GPIO,
		TRIGGER_GPIO,
		ECHO_GPIO,
		RX_GPIO,
		TX_GPIO,
		SPEAKER_GPIO,
		SPI_SCLK_GPIO,
		GRN_LED_GPIO,
		I2C_SDA_GPIO,
		I2C_SCL_GPIO,
		RED_LED_GPIO,
		DIR_GPIO,
		STEP_GPIO,
		ENC_A_GPIO,
		TOUCH_BUTTON_GPIO,
		ENC_SW_GPIO,
		LDR_xTC_GPIO,
		ENC_B_GPIO,
		POT_GPIO,
		MIC_GPIO
	};

	for (int i = 0; i < (sizeof(allPins) / sizeof(int)); i++)
	{
		pinMode(allPins[i], INPUT);
	}
}

// check if user wants to abort current test
testResult abortCurrentTest() {

	if (Serial.available()) {
		byte read = Serial.read();
		switch (read) {
		case 'x':
			return TEST_ABORTED; //return with abort code
			break;
		}
	}
	else
	{
		return TEST_DONE_OK;
	}
	return TEST_DONE_OK;
}


void restoreUsedPins(int p1, int p2, int p3) {

	Serial.print("Restoring pin: ");
	Serial.println(p1);
	pinMode(p1, INPUT);

	//if (p2>=0)
	{
		Serial.print("Restoring pin: ");
		Serial.println(p2);
		pinMode(p2, INPUT);
	}

	//if (p3>=0)
	{
		Serial.print("Restoring pin: ");
		Serial.println(p3);
		pinMode(p3, INPUT);
	}
}

void restoreUsedPins(int p1, int p2) {

	Serial.print("Restoring pin: ");
	Serial.println(p1);
	pinMode(p1, INPUT);

	//if (p2 >= 0)
	{
		Serial.print("Restoring pin: ");
		Serial.println(p2);
		pinMode(p2, INPUT);
	}
}

void restoreUsedPins(int p1) {

	Serial.print("Restoring pin: ");
	Serial.println(p1);
	pinMode(p1, INPUT);
}


testResult initTest(const char* testName, bool waitOK, bool waitStart) {

	pinMode(ENC_SW_GPIO, INPUT_PULLUP);

	Serial.println("--------------------------");
	Serial.print("Testing ");
	Serial.println(testName);
	Serial.println("--------------------------");
	Serial.println();

	if (waitStart)
	{
		Serial.println("Press ENC switch to start testing");
		Serial.println("send 'x' to abort");
		Serial.println();

		delay(300);

		while (digitalRead(ENC_SW_GPIO))
		{
			if (abortCurrentTest())
				return  TEST_ABORTED;
		}
		delay(300);
	}

	Serial.print("...start testing ");
	Serial.println(testName);
	Serial.println("send 'x' to abort");
	Serial.println();

	if (waitOK)
	{
		Serial.print("press ENC switch to confirm ");
		Serial.print(testName);
		Serial.println(" OK");
		Serial.println();
	}

	return TEST_DONE_OK;
}

void printTestOK(const char* testName) {
	Serial.println();
	Serial.print(testName);
	Serial.println(" OK!");
	Serial.println();
}

tests DemoMenu::getMenuItem(int index) {
	return this->menuItems[index];
}

int DemoMenu::getMenuItemsN(){
	return sizeof(this->menuItems) / sizeof(tests);
}

const char* DemoMenu::getMenuItemString(int index) {
	return this->menuItemsStr[index];
}


Button::Button(int btnGpio, int debounceInterval)
	: m_btnGpio{ btnGpio }
{
	m_button = Bounce();
	m_button.attach(m_btnGpio, INPUT_PULLUP); // Attach the debouncer to ENC_SW_GPIO pin with INPUT_PULLUP mode
	m_button.interval(debounceInterval);
}

void Button::update() {
	this->m_button.update();
}

bool Button::isRising() {
	return this->m_button.rose();
}

bool Button::isFalling() {
	return this->m_button.fell();
}

bool Button::state() {
	return this->m_button.read();
}


void initTest(const char* testName) {

	Serial.println("--------------------------");
	Serial.print("Testing ");
	Serial.println(testName);
	Serial.println("--------------------------");
	Serial.println();

	Serial.print("...start testing ");
	Serial.println(testName);
	Serial.println("send 'x' to abort");
	Serial.println();

}

