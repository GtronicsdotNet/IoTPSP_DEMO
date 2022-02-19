
#include "IoTPSP_DEMO_DHT.h"
#include "IoTPSP_DEMO_pin_definition.h"
#include <DHT.h>;

#define DHT_TYPE DHT22    // DHT 22


testResult testDHT(OledHmi* ui, Button* encoderSwitch){

	unsigned long lastMeasureMs = 0;

	bool exitDemo = false;
	bool measure = true; 

	const char* title = "DHT22 DEMO";
	const char* description = "Humidity = ";
	//const char* istruction = "";
	const char* noDhtMessage = "Check DHT connection!";

	String displayMessage = String(noDhtMessage);

	float humidity;  //Stores humidity value
	float temperature; //Stores temperature value

	//delay(300);

	Serial.println(title);
	Serial.println("send 'x' to abort");
	Serial.println("press ENC switch to exit DHT");
	Serial.println();


	//DHT dht(IoTPSP().dht_gpio, DHT_TYPE);
	DHT dht(DHT_GPIO, DHT_TYPE);
	dht.begin();


	while (!exitDemo)
	{
		if (measure && millis() - lastMeasureMs > 500)
		{
			//Read data and store it to variables hum and temp
			humidity = dht.readHumidity();
			temperature = dht.readTemperature();
			//Print temp and humidity values to serial monitor
			
			if (!isnan(humidity))
			{
				Serial.print("Humidity: ");
				Serial.print(humidity);
				Serial.print(" %, Temp: ");
				Serial.print(temperature);
				Serial.println(" C");

				displayMessage = String(
					String(humidity,1) +
					String("% - Temp: ") +
					String(temperature,1) +
					String('c')
				);
			}
			else
			{
				Serial.println(noDhtMessage);
				displayMessage = String(noDhtMessage);
			}
			lastMeasureMs = millis();
		}

		ui->displayDemoScreen(title, description, displayMessage);


		if (abortCurrentTest())
			exitDemo = true;

		encoderSwitch->update();
		if (encoderSwitch->isRising())
			exitDemo = true;
	}

	return TEST_DONE_OK;

}