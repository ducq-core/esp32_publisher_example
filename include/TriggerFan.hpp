#pragma once

#include "Trigger.hpp"

#include "ISwitch.hpp"
#include "ISinkSwitch.hpp"
#include "MeteoSource.hpp"
#include "IMeteoSpecification.hpp"


class TriggerFan: public Trigger {
private:
	ISwitch *fan;
	IMeteoSpecification *spec;
	MeteoSource *source;
	ISinkSwitch *sink;

public:
	TriggerFan(ISwitch *fan,
		IMeteoSpecification *spec,
		MeteoSource *source,
		ISinkSwitch *sink,
		time_t refreshRate
	);
	void onPoll() override;
};