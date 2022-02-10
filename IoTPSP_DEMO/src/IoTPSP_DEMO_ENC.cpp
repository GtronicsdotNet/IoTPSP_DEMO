// 
// 
// 

#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_ENC.h"


//**************** test ENCODER **********************
#define SWITCH_OK        B00000001
#define ROTATING_CW_OK   B00000010
#define ROTATING_CCW_OK  B00000100

constexpr int nPulses = 10;

testTypeResult testENCODER() {

    constexpr tests testType = ENCODER;

    char testStatus = 0;
    int encoderPosition = 0;
    int encoderLastA = LOW;
    bool currentEncA = LOW;
    int direction = 1;
    bool printEncoderPosition = true;
    pinMode(ENC_A_GPIO, INPUT_PULLUP);
    pinMode(ENC_B_GPIO, INPUT_PULLUP);
    pinMode(ENC_SW_GPIO, INPUT_PULLUP);

    enum encoderDirection {
        UNKNOWN,
        ROTATING_CCW,
        ROTATING_CW
    };

    encoderDirection currentEncoderDirection = UNKNOWN;
    encoderDirection lastEncoderDirection = UNKNOWN;

    Serial.print("Testing ENCODER: rotate the encoder CCW, then CW then click it");
    Serial.println();

    while (testStatus != (SWITCH_OK | ROTATING_CCW_OK | ROTATING_CW_OK)) {

        if (abortCurrentTest()) {
            restoreUsedPins(ENC_A_GPIO, ENC_B_GPIO, ENC_SW_GPIO);
            return { testType, TEST_ABORTED };
        }

        currentEncA = digitalRead(ENC_A_GPIO);
        if ((encoderLastA == LOW) && (currentEncA == HIGH)) {
            if (digitalRead(ENC_B_GPIO) == LOW) {
                //encoderPosition++;
                direction = 1;
                currentEncoderDirection = ROTATING_CW;
            }
            else {
                //encoderPosition--;
                direction = -1;
                currentEncoderDirection = ROTATING_CCW;
            }

            if (lastEncoderDirection != currentEncoderDirection)
                encoderPosition = 0;

            encoderPosition += direction;

            printEncoderPosition = true;

            if (encoderPosition < 0 && (testStatus & ROTATING_CCW_OK))
                printEncoderPosition = false;

            if (encoderPosition > 0 && (testStatus & ROTATING_CW_OK))
                printEncoderPosition = false;

            if (printEncoderPosition)
            {
                Serial.print("Encoder Position: ");
                Serial.println(encoderPosition);
            }

            lastEncoderDirection = currentEncoderDirection;
        }
        encoderLastA = currentEncA;


        if (!digitalRead(ENC_SW_GPIO)) //check switch pressed
        {
            if (!(testStatus & SWITCH_OK)) //if is the first press 
            {
                Serial.println("ENCODER SWITCH OK!");
            }
            testStatus |= SWITCH_OK;
        }

        if (encoderPosition < (nPulses * -1)) //check if CCW is OK
        {
            if (!(testStatus & ROTATING_CCW_OK))
            {
                Serial.println("ENCODER CCW ROTATION OK!");
            }
            testStatus |= ROTATING_CCW_OK;
        }

        if (encoderPosition > nPulses)
        {
            if (!(testStatus & ROTATING_CW_OK))
            {
                Serial.println("ENCODER CW ROTATION OK!");
            }
            testStatus |= ROTATING_CW_OK;
        }


    }

    Serial.println();
    Serial.println("ENCODER OK!");
    Serial.println();

    restoreUsedPins(ENC_A_GPIO, ENC_B_GPIO, ENC_SW_GPIO);
    return { testType, TEST_DONE_OK };
}


// 
// 
// 

#include "IoTPSP_DEMO_ENC.h"


