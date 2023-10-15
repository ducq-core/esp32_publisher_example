#include <stdio.h>

#include "DucqSink.hpp"


DucqSink::DucqSink(
	const char *host, 
	const char *port,
	char *switchRoute,
	char *meteoRoute,
	IDisplayStatus *display
):
	state(DUCQ_OK),
	ducq(ducq_new_tcp(host, port)),
	switchRoute(switchRoute),
	meteoRoute(meteoRoute),
	display(display)
{}


void DucqSink::save(Meteo *meteo) {
	char payload[256] = "";
	size_t size = snprintf(payload, 256,
		"{"
			"temperature:%.2f,"
			"humidity:%.2f,"
			"pressure:%.2f,"
			"gas:%.2f"
		"}",
		meteo->temperature,
		meteo->humidity,
		meteo->pressure,
		meteo->gas
	);

	state = ducq_publish(ducq, meteoRoute, payload, size);

	display->display(ducq_state_tostr(state));
}


void DucqSink::save(bool isOn) {
	char payload[16] = "";
	size_t size = snprintf(payload, 16, "{switch:%s}", isOn ? "true" : "false");

	state = ducq_publish(ducq, switchRoute, payload, size);

	display->display(ducq_state_tostr(state));
}
