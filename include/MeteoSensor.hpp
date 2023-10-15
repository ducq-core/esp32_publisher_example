#pragma once

#include <Adafruit_BME680.h>


class MeteoSensor {
private:
	Adafruit_BME680 bme;

public:
	MeteoSensor(int CS, int MOSI, int MISO, int SCK );

	bool init();
	bool performReading();
	
	float temperature();
	float pressure();
	float humidity();
	float gas_resistance();
};