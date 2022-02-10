// 
// 
// 

#include "IoTPSP_DEMO_pin_definition.h"
#include "IoTPSP_DEMO_TOUCH.h"



//**************** test TOUCH **********************

testTypeResult testTOUCH() {

    constexpr tests testType = TOUCH;

    //pinMode(RED_LED, OUTPUT);
    //pinMode(GRN_LED, OUTPUT);
    pinMode(TOUCH_BUTTON_GPIO, INPUT);

    enum testStates {
        TOUCH_OFF,
        TOUCH_ON,
        TOUCH_OK,
        TOUCH_ABORT,
        TOUCH_ERR
    };

    testStates testState = TOUCH_OFF;

    Serial.print("Testing TOUCH: touch the touch pad");
    Serial.println();


    Serial.print("Current touch pad state is: ");

    bool currTouchState = digitalRead(TOUCH_BUTTON_GPIO);

    if (currTouchState)
    {
        Serial.println("TOUCH ON");
        Serial.println();
        Serial.print("!!! ERROR !!! : ");
        Serial.println("TOUCH MUST BE OFF TO START TOUCH TEST");
        Serial.println();
        testState = TOUCH_ERR;
        return { testType, TEST_DONE_ERROR };
    }
    else
    {
        Serial.println("TOUCH OFF");
        //all ok proceed with testing
        testState = TOUCH_OFF;
    }

    while (testState != TOUCH_OK) {
        //state machine
        currTouchState = digitalRead(TOUCH_BUTTON_GPIO); //read current touch state

        if (abortCurrentTest())
            return { testType, TEST_ABORTED };

        switch (currTouchState) {
        case HIGH: //touch is on
            testState = TOUCH_OK;
            break;

        case LOW: //touch is off
            break;
        }
    }

    Serial.println();
    Serial.println("TOUCH OK!");
    Serial.println();

    return { testType, TEST_DONE_OK };


}



