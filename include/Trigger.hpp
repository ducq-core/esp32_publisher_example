#pragma once

#include <time.h>

class Trigger {
private:
	time_t lastRefresh;
	time_t refreshRate;

protected:
	virtual void onPoll();

public:
	Trigger(time_t refreshRate);
	virtual void init();
	virtual void poll();
};