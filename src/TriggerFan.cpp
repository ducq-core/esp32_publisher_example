#include "TriggerFan.hpp"

TriggerFan::TriggerFan(
		ISwitch *fan,
		IMeteoSpecification *spec,
		MeteoSource *source,
		ISinkSwitch *sink,
		time_t refreshRate
):
	Trigger(refreshRate),
	fan(fan),
	spec(spec),
	source(source),
	sink(sink)
 {}

	
void TriggerFan::onPoll() {
	Meteo meteo = source->getMeteo();

	if(spec->isSatisfiedBy(&meteo) != fan->getState()) {
			fan->turn( ! fan->getState());
			sink->save(  fan->getState());
		}
}