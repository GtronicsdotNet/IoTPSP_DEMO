#pragma once

//#define SET_TIME_FROM_HOST_PC //comment this line if your DS3231 has a battery and the time and and has already 

struct Greeting {
	const char* hiTo = "CIAO xxxxxx!";	//custom hi message
	int leftIndentOffset = 33;			//offset to have hi message centered in the display
};

