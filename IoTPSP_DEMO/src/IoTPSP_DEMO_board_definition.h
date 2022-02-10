#pragma once

//#define TEST_ARDUINO_NANO
#define TEST_WEMOS_D1_MINI_ESP32

#if defined(TEST_ARDUINO_NANO) && defined(TEST_WEMOS_D1_MINI_ESP32)
#error Multiple board definition
#endif