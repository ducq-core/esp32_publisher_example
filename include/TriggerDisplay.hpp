#pragma once

#include "Trigger.hpp"

#include "IDisplayMeteo.hpp"
#include "MeteoSource.hpp"


class TriggerDisplay: public Trigger {
private:
	IDisplayMeteo *display;
	MeteoSource *source;

public:
	TriggerDisplay(IDisplayMeteo *display, MeteoSource *source, time_t refreshRate);
	void onPoll() override;
};