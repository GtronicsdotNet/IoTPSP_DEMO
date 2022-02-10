/*
 Name:		IoTPSP_DEMO.ino
 Created:	09-Feb-22 19:28:55
 Author:	gtronics
*/

//#include "src\IoTPSP_DEMO_OLED_HMI.h"
#include "src\IoTPSP_DEMO_serial_HMI.h"
#include "src\IoTPSP_DEMO_testing.h"



// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(115200);
	Serial.println();
	Serial.println("-----------------------");
	Serial.println("- IoTPSP DEMO program -");
	Serial.println("-----------------------");
	Serial.println();
	printSerialHMI();
	Serial.println();
}


// the loop function runs over and over again until power down or reset
void loop() {
	testResult tr = TEST_DONE_OK;
	if (Serial.available()) {
		byte read = Serial.read();
		tr = TEST_RUNNING;
		if (read != 0xD) {
			switch (read) {
			case 'a':
				//risultatoTest = testIoTPSP(ALL);
				break;

			case 'p':
				tr = testIoTPSP(POT);
				break;

			case 'l':
				tr = testIoTPSP(LEDs);
				break;

			case 't':
				tr = testIoTPSP(TOUCH);
				break;

			case 'e':
				tr = testIoTPSP(ENCODER);
				break;

			case 'o':
				tr = testIoTPSP(OLED);
				break;

			case 'c':
				//risultatoTest = testIoTPSP(LCD);
				break;

			case 'r':
				//risultatoTest = testIoTPSP(RELAY);
				break;

			case 'h':
				//risultatoTest = testIoTPSP(HCSR04);
				break;

			case 'd':
				//risultatoTest = testIoTPSP(DHTxx);
				break;

			case 'm':
				//risultatoTest = testIoTPSP(MIC);
				break;

			case 'y':
				//risultatoTest = testIoTPSP(MP3);
				break;

			case 's':
				//risultatoTest = testIoTPSP(SDCARD);
				break;

			case 'z':
				//risultatoTest = testIoTPSP(RTCDS);
				break;

			case 'n':
				//risultatoTest = testIoTPSP(LDRxTC);
				break;

			case 'w':
				//risultatoTest = testIoTPSP(MOTOR);
				break;

			case 'q':
				//risultatoTest = testIoTPSP(LEVELSHIFTER);
				break;

			case 'u':
				//risultatoTest = testIoTPSP(DIGITALJ3J34);
				break;

			default:
				Serial.println();
				Serial.print("WRONG SELECTION, to start testing ");
				printSerialHMI();
				break;

			}

			Serial.flush();

			if (tr == TEST_DONE_OK) { //OK
			  //no error
				Serial.println();
				Serial.print("******** Done OK! ********");
				Serial.println();
			}

			if (tr == TEST_DONE_ERROR) { //ERROR
			  //ERROR
				Serial.println();
				Serial.println("******** Done ERROR ********");
				Serial.println();
			}

			if (tr == TEST_ABORTED) { //ABORT
			  //ABORT
				Serial.println();
				Serial.println("******** ABORTED ********");
				Serial.println();
			}

			if (tr != TEST_RUNNING) {
				Serial.println();
				Serial.print("To restart the testing procedure ");
				Serial.println();
				printSerialHMI();
			}

			Serial.println();
			Serial.println();
		}
	}

}

