#pragma once


#include "Trigger.hpp"
#include "MeteoSource.hpp"
#include "ISinkMeteo.hpp"


class TriggerSaveMeteo: public Trigger {
private:
	MeteoSource *source;
	ISinkMeteo *sink;

	void saveMeteo();

public:
	TriggerSaveMeteo(MeteoSource *source, ISinkMeteo *sink, time_t refreshRate);
	void onPoll() override;
};