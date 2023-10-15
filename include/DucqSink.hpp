#pragma once

#include "ISinkMeteo.hpp"
#include "ISinkSwitch.hpp"
#include "IDisplayStatus.hpp"

#include <ducq.hpp>

class DucqSink: public ISinkMeteo, public ISinkSwitch {
private:
	ducq_state state;
	ducq_i *ducq;
	char *switchRoute;
	char *meteoRoute;
	IDisplayStatus *display;

public:
	DucqSink(
		const char *host, 
		const char *port,
		char *switchRoute,
		char *meteoRoute,
		IDisplayStatus *display
	);
	void save(Meteo *meteo) override;
	void save(bool isOn) override;
};