#pragma once

#include <esp_event_loop.h>

class Wifi {
private:
	const char *ssid;
	const char *password;


public:
	Wifi(const char *ssid, const char *password);

	bool init();
	const char *getIp();
	// system_event_id_t getState();
	// bool isInitialised();
};