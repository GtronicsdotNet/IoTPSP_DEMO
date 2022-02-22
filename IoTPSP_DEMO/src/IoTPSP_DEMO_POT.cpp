// 
// 
// 

#include "IoTPSP_DEMO_board_definition.h"
#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_POT.h"


//**************** test POT **********************

#ifdef TEST_ARDUINO_NANO
constexpr int POTminADValue = 10;
constexpr int POTmaxADValue = 690;
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
constexpr int POTminADValue = 10;
constexpr int POTmaxADValue = 4080;
#endif


testResult testPOT(OledHmi* ui, Button* encoderSwitch){

    bool updateUi = true;
    bool exitPOTDemo = false;
    int curAD = 0; //analog read
    int lastAD = 0; //last analog read
    const char* istruction = "Rotate POT to test!";

    const char* title = "POT DEMO";
    const char* description = "POT position = ";

    Serial.print(title);
    Serial.println("press ENC switch to exit");
	Serial.println("send 'x' to exit");
    Serial.println();
    
    
    while (!exitPOTDemo) {
        //state machine
        curAD = analogRead(POT_GPIO); //pot is on A6

        updateUi = true;
        if (updateUi)
        {
			Serial.print(description);
			Serial.print(curAD);
			Serial.println();

            ui->displayDemoScreen(title, description, String(curAD), istruction);

            updateUi = false;
        }

		if (abortCurrentTest())
			exitPOTDemo = true;

        encoderSwitch->update();
        if(encoderSwitch->isRising())
            exitPOTDemo = true;
        
        delay(100);
    }
    
    return TEST_DONE_OK;
}

