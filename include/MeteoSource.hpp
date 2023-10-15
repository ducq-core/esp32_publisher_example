#pragma once

#include "MeteoValueObject.hpp"
#include "MeteoSensor.hpp"

#include <Trigger.hpp>

class MeteoSource: public Trigger {
private:
	MeteoSensor *sensor;
	Meteo meteo;
	
	void _getMeteo();

public:
	MeteoSource(MeteoSensor *sensor, time_t refreshRate);
	void onPoll() override;
	Meteo getMeteo();
};