#pragma once

#include "ISwitch.hpp"

class SwitchByPin: public ISwitch {
private:
	int pin;
	bool state;

public:
	SwitchByPin(int pin);
	void turnOn() override;
	void turnOff() override;
	void turn(bool state) override;
	bool getState() override;
};