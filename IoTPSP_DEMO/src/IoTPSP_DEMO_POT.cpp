// 
// 
// 

#include "IoTPSP_DEMO_board_definition.h"
#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_POT.h"

//**************** test POT **********************
#define POTmin 10
#define POTmax 20
#define POTmid 30
#define POTok 40
#define POTexit 1001
#define chkPOT 0

#ifdef TEST_ARDUINO_NANO
constexpr int POTminADValue = 10;
constexpr int POTmaxADValue = 690;
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
constexpr int POTminADValue = 10;
constexpr int POTmaxADValue = 4080;
#endif


constexpr int POTmidADValue = POTminADValue + ((POTmaxADValue - POTminADValue) / 2);

testTypeResult testPOT() {

    tests testType = POT;

    int stato = 0; //define state machine
    int curAD = 0; //analog read
    char POTpos = 0;

    pinMode(GRN_LED_GPIO, OUTPUT);
    pinMode(RED_LED_GPIO, OUTPUT);
    digitalWrite(GRN_LED_GPIO, HIGH);
    digitalWrite(RED_LED_GPIO, HIGH);

    Serial.print("Testing POT: move to min-mid-max");
    Serial.println();

    Serial.print("POT current position is = ");
    Serial.print(analogRead(POT_GPIO));
    Serial.println();
    
    while (stato < 1000) {
        //state machine
        curAD = analogRead(POT_GPIO); //pot is on A6

        if (abortCurrentTest())
        {
            restoreUsedPins(GRN_LED_GPIO, RED_LED_GPIO);
            return { testType, TEST_ABORTED };
        }

        switch (stato) {

        case chkPOT:
            //check POT position
            if (curAD < POTminADValue)
                stato = POTmin;

            if (curAD > POTmaxADValue)
                stato = POTmax;

            if (curAD > POTmidADValue - 10 && curAD < POTmidADValue + 10)
                stato = POTmid;

            if ((POTpos & B00000111) == B00000111)
                stato = POTok;

            break;

        case POTmin:
            //POT is at min position
            if ((POTpos & 0x01) != 0x01) {
                Serial.print("POT min position reached = ");
                Serial.print(curAD);
                Serial.println();
            }
            POTpos |= 0x01;
            stato = chkPOT;
            break;

        case POTmid:
            //POT is at mid position
            if ((POTpos & 0x02) != 0x02) {
                Serial.print("POT mid position reached = ");
                Serial.print(curAD);
                Serial.println();
            }
            POTpos |= 0x02;
            stato = chkPOT;
            break;


        case POTmax:
            //POT is at max position
            if ((POTpos & 0x04) != 0x04) {
                Serial.print("POT max position reached = ");
                Serial.print(curAD);
                Serial.println();
            }
            POTpos |= 0x04;
            stato = chkPOT;
            break;

        case POTok:
            stato = POTexit;
            Serial.println();
            Serial.print("POT OK!");
            Serial.println();
            restoreUsedPins(GRN_LED_GPIO, RED_LED_GPIO);
            return { testType, TEST_DONE_OK };
            break;

        }
    }
    

    return { testType, TEST_DONE_OK };

}

