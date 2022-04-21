# IoTPSP_DEMO
Demo sketch useful to test the IoT Proto Shield Plus on-board features and Plug and Play modules

Ver 1.4
-------
- added file IoTPSP_Compile_Options.h
	- set custom greetings
	- define SET_TIME_FROM_HOST_PC

Ver 1.3
-------
- Minor fixes to remove encoder spurious detection
- Minor changes in the UI

Ver 1.2
-------
- Merged encoder-enhancement branch into master
	- Added possibility to handle encoder A and B signal with interrupts (it's now the default setting)  


Ver 1.1
-------
Minor improvements on the displaying of the selection list


Ver 1.0
-------
It works with a ESP32 D1 MINI controller board.
The on-board devices and plug and play modules included in this test sketch are:
- plug and play OLED DISPLAY SSD1306 128x64 module (needed to display the UI)
- on-board ENCODER (used to navigate the UI on the OLED DISPLAY)
- on-board LEDs
- on-board TOUCH
- on-board POT
- plug and play RTC module
- plug and play RELAY module
- plug and play HC-SR04 module
- plug and play DHT22 module
- plug and play MICROPHONE MAX 9814 module
- plug and play MP3 DF-PLAYER MINI

ENCODER is implemented in "simple mode" (doesn't use interrupts)

