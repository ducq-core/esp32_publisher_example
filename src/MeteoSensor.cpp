#include "MeteoSensor.hpp"

#define SEALEVELPRESSURE_HPA (1013.25)


MeteoSensor::MeteoSensor (int CS, int MOSI, int MISO, int SCK) :
	bme(CS, MOSI, MISO, SCK)
{
	// if (!bme.begin()) {
  //   Serial.println("Could not find a valid BME680 sensor, check wiring!");
  //   while (1);
//   // }

//   // Set up oversampling and filter initialization
//   bme.setTemperatureOversampling(BME680_OS_8X);
//   bme.setHumidityOversampling(BME680_OS_2X);
//   bme.setPressureOversampling(BME680_OS_4X);
//   bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
//   bme.setGasHeater(320, 150); // 320*C for 150 ms
}


bool MeteoSensor::init() {
	if (!bme.begin())
		return false;

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

	return true;
}

bool MeteoSensor::performReading() {
	return bme.performReading();
}
float MeteoSensor::temperature() {
	return bme.temperature;
}
float MeteoSensor::pressure() {
	return bme.pressure / 100.0;
}
float MeteoSensor::humidity() {
	return bme.humidity;
}
float MeteoSensor::gas_resistance() {
	return bme.gas_resistance / 1000.0;
}