#include <Arduino.h> // Serial

#include "secrets.h"

#include "Program.hpp"
#include "Trigger.hpp"

#include "Lcd16x20Display.hpp"

#include "MeteoSensor.hpp"
#include "MeteoSource.hpp"

#include "DucqSink.hpp"

#include "SwitchByPin.hpp"
#include "DewPointSpecification.hpp"

#include "TriggerDisplay.hpp"
#include "TriggerSaveMeteo.hpp"
#include "TriggerFan.hpp"


Program::Program() :
	wifi(SSID, WIFIPASS)
{
	Serial.begin(BAUD_RATE);
	while(!Serial) ;
	Serial.println("\n\nstarting...");

	Lcd16x20Display *lcd = new Lcd16x20Display(I2C_DISPLAY_ADDR);
	
	if(!wifi.init()) {
		lcd->display("wifi init failed.");
		while(1);
	}
	lcd->display(wifi.getIp());

	MeteoSensor *sensor = new MeteoSensor(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
	if(!sensor->init()) {
		lcd->display("BME680 wiring.");
		while(1);
	}
	MeteoSource *source = new MeteoSource(sensor, SENSOR_REFRESH_RATE);

	DucqSink *ducqSink = new DucqSink(DUCQ_HOST, DUCQ_PORT, DUCQ_SWITCH_ROUTE, DUCQ_METEO_ROUTE, lcd);

	SwitchByPin *fan = new SwitchByPin(FAN_PIN);
	DewPointSpecification *fanSpec = new DewPointSpecification(FAN_HUMIDITY_THRESHOLD);
	
	triggers.push_back(source); // this one first
	triggers.push_back(new TriggerDisplay(lcd, source, DISPLAY_REFRESH_RATE));
	triggers.push_back(new TriggerSaveMeteo(source, ducqSink, SAVE_REFRESH_RATE));
	triggers.push_back(new TriggerFan(fan, fanSpec, source, ducqSink, FAN_CHECK_REFRESH_RATE));

	std::vector<Trigger*>::iterator it = triggers.begin();
	while(it != triggers.end()) {
		Trigger *trigger = (Trigger *)*it;
		trigger->init();
		++it;
	}
}


void Program::loop() {
	std::vector<Trigger*>::iterator it = triggers.begin();
	while(it != triggers.end()) {
		Trigger *trigger = (Trigger *)*it;
		trigger->poll();
		++it;
	}
}