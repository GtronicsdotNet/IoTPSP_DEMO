
#include "IoTPSP_DEMO_RTC.h"

#include "RTClib.h"

#define SET_TIME_FROM_HOST_PC //comment this line if your DS3231 has a battery and the time and and has already 

testResult testRTCDS(OledHmi* ui, Button* encoderSwitch) {

	bool exitDemo = false;
	bool rtcOk = true;
	unsigned long lastRefresh = 0;

	const char* title = "RTC DEMO";
	const char* description = "RTC date and time (CET) = ";
	const char* rtcKoMessage = "Couldn't find RTC";
	String rtcMessage = String(rtcKoMessage);

	initTest(title);

	RTC_DS3231 rtc; //define the rtc object

	if (!rtc.begin()) {
		Serial.println(rtcKoMessage);
		Serial.flush();
		ui->displayDemoScreen(title, description, rtcMessage);

		while (!exitDemo)
		{
			encoderSwitch->update();
			if (encoderSwitch->isRising())
				exitDemo = true;
		}

		//abort();
		rtcOk = false;
	}

#ifdef SET_TIME_FROM_HOST_PC
	// the following line sets the RTC to the date & time this sketch was compiled
	if(rtcOk)
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //set the time and date on the DS3231
#endif

	//DateTime pcDayTime = DateTime(F(__DATE__), F(__TIME__));


	while (!exitDemo)
	{
		if (rtcOk && (millis()-lastRefresh)>1000) {
			
			DateTime now = rtc.now();

			Serial.print("Date red from RTC module: ");
			Serial.print(now.day(), DEC);
			Serial.print('/');
			Serial.print(now.month(), DEC);
			Serial.print('/');
			Serial.print(now.year(), DEC);
			Serial.println();

			Serial.print("Time red from RTC module: ");
			Serial.print(now.hour(), DEC);
			Serial.print(':');
			Serial.print(now.minute(), DEC);
			Serial.print(':');
			Serial.print(now.second(), DEC);
			Serial.println();

			//Serial.print("Temperature red from RTC module: ");
			//Serial.print(rtc.getTemperature());
			//Serial.println(" C");

			Serial.println();

			rtcMessage = String(
				String(now.day(), DEC) + "/" +
				String(now.month(), DEC) + "/" +
				String(now.year(), DEC) + " - " +
				String(now.hour(), DEC) + ":" +
				String(now.minute(), DEC) + ":" +
				String(now.second(), DEC)
			);

			ui->displayDemoScreen(title, description, rtcMessage);
			
			lastRefresh = millis();
		}


		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if (encoderSwitch->isRising())
			exitDemo = true;

		//delay(100);

	}


	return TEST_DONE_OK;

}

