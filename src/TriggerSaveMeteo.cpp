
#include "TriggerSaveMeteo.hpp"

TriggerSaveMeteo::TriggerSaveMeteo(MeteoSource *source, ISinkMeteo *sink, time_t refreshRate):
	Trigger(refreshRate),
	source(source),
	sink(sink)
{}


void TriggerSaveMeteo::onPoll() {
	Meteo meteo = source->getMeteo();
	sink->save(&meteo);
}	
