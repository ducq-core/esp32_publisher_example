#include "TriggerDisplay.hpp"

TriggerDisplay::TriggerDisplay(IDisplayMeteo *display, MeteoSource *source, time_t refreshRate) :
	Trigger(refreshRate),
	display(display),
	source(source)
{}

void TriggerDisplay::onPoll() {
	Meteo meteo = source->getMeteo();
	display->display(&meteo);
}