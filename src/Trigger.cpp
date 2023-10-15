#include "Trigger.hpp"


Trigger::Trigger(time_t refreshRate):
	lastRefresh(0),
	refreshRate(refreshRate)
{}


void Trigger::onPoll() {}


void Trigger::init() {
	lastRefresh = time(NULL); 
	onPoll();
}

void Trigger::poll() {
	time_t now = time(NULL);
	
	if(now - lastRefresh > refreshRate) {
		lastRefresh += refreshRate;
		onPoll();
	}
}