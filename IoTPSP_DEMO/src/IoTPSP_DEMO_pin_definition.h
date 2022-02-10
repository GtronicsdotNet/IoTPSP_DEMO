#pragma once


#include "arduino.h"
#include "IoTPSP_DEMO_board_definition.h"


#ifdef TEST_ARDUINO_NANO
//definition for ARDUINO NANO boards
#define SERVO_GPIO			5	//define SERVO pin
#define SPI_CS_GPIO			10	//define SPI_CS pin
#define RELAY_GPIO			8	//define I/O number to drive the relay
#define DHT_GPIO			9	//define data pin connected to DHT sensor
#define TRIGGER_GPIO		6	//define HCSR04 trigger pin
#define ECHO_GPIO			7	//define HCSR04 echo pin
#define RX_GPIO				0
#define TX_GPIO				1
#define SPEAKER_GPIO		1
#define SPI_SCLK_GPIO		13
#define GRN_LED_GPIO		12	//define pin number for green LED
#define I2C_SDA_GPIO		A4	//define pin number for I2C SDA
#define I2C_SCL_GPIO		A5	//define pin number for I2C SCL
#define RED_LED_GPIO		11	//define pin number for red LED
#define DIR_GPIO			4	//define DIR pin for motor
#define STEP_GPIO			3	//define STEP pin for motor
#define ENC_A_GPIO			2	//assign pin for rotary encoder A
#define TOUCH_BUTTON_GPIO	A0	//define I/O number for touch button
#define ENC_SW_GPIO			A1	//assign pin for rotary encoder switch
#define	LDR_xTC_GPIO		A2
#define ENC_B_GPIO			A3  //assign pin for rotary encoder B
#define POT_GPIO			A6	//define pin number for POT
#define MIC_GPIO			A7	//define data pin connected to MIC
#endif

#ifdef TEST_WEMOS_D1_MINI_ESP32
	//definition for ARDUINO NANO boards
#define SERVO_GPIO			4	//define SERVO pin
#define SPI_CS_GPIO			5	//define SPI_CS pin
#define RELAY_GPIO			12	//define I/O number to drive the relay
#define DHT_GPIO			13	//define data pin connected to DHT sensor
#define TRIGGER_GPIO		14	//define HCSR04 trigger pin
#define ECHO_GPIO			15	//define HCSR04 echo pin
#define RX_GPIO				16
#define TX_GPIO				17
#define SPEAKER_GPIO		17
#define SPI_SCLK_GPIO		18
#define GRN_LED_GPIO		19	//define pin number for green LED
#define I2C_SDA_GPIO		21	//define pin number for I2C SDA
#define I2C_SCL_GPIO		22	//define pin number for I2C SCL
#define RED_LED_GPIO		23	//define pin number for red LED
#define DIR_GPIO			25	//define DIR pin for motor
#define STEP_GPIO			26	//define STEP pin for motor
#define ENC_A_GPIO			27	//assign pin for rotary encoder A
#define TOUCH_BUTTON_GPIO	32	//define I/O number for touch button
#define ENC_SW_GPIO			33	//assign pin for rotary encoder switch
#define	LDR_xTC_GPIO		34
#define ENC_B_GPIO			35  //assign pin for rotary encoder B
#define POT_GPIO			36	//define pin number for POT
#define MIC_GPIO			39	//define data pin connected to MIC
#endif
