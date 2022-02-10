// 
// 
// 

#include "IoTPSP_DEMO_board_definition.h"
#include "IoTPSP_DEMO_serial_HMI.h"
#include "arduino.h"

#ifdef TEST_ARDUINO_NANO
const char* board_under_test = "ARDUINO NANO";
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
const char* board_under_test = "ESP32 WEMOS D1 MINI";
#endif


void printSerialHMI() {
	Serial.print("Testing board: ");
	Serial.println(board_under_test);
	Serial.println();
	Serial.println("Press:");
	Serial.println("  - 'a' to perform all tests");
	Serial.println("  - 'l' to perform LEDs test");
	Serial.println("  - 'p' to perform POT test");
	Serial.println("  - 't' to perform TOUCH test");
	Serial.println("  - 'e' to perform ENCODER test");
	Serial.println("  - 'o' to perform OLED display test");
	Serial.println("  - 'c' to perform LCD display test");
	Serial.println("  - 'r' to perform RELAY test");
	Serial.println("  - 'h' to perform HCSR04 test");
	Serial.println("  - 'd' to perform DHT test");
	Serial.println("  - 'm' to perform MIC test");
	Serial.println("  - 'y' to perform MP3 player test");
	Serial.println("  - 'z' to perform RTC test");
	Serial.println("  - 's' to perform SD-CARD test");
	Serial.println("  - 'n' to perform LDR/nTC test");
	Serial.println("  - 'w' to perform MOTOR test");
	Serial.println("  - 'q' to perform LEVEL SHIFTER test");
	Serial.println("  - 'u' to perform digital pin J3 J34");

}

