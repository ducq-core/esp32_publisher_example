#include "MeteoSource.hpp"



MeteoSource::MeteoSource(MeteoSensor *sensor, time_t refreshRate):
	Trigger(refreshRate),
	sensor(sensor),
	meteo({})
{}

void MeteoSource::onPoll() {
	if(sensor->performReading() ) {
		meteo.temperature = sensor->temperature();
		meteo.humidity    = sensor->humidity();
		meteo.pressure    = sensor->pressure();
		meteo.gas         = sensor->gas_resistance();
	}
}

Meteo MeteoSource::getMeteo() {
	return meteo;
}

