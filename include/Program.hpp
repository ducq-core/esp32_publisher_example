#pragma once

#include <vector>

#include "Wifi.hpp"
#include "Trigger.hpp"

class Program {
private:
	Wifi wifi;
	std::vector<Trigger*> triggers;
	
public:
	Program();
	void loop();
};