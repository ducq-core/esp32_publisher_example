#include <Arduino.h>

#include "SwitchByPin.hpp"


SwitchByPin::SwitchByPin(int pin):
	pin(pin),
	state(false)
{
	digitalWrite(pin, LOW);
}

void SwitchByPin::turnOn() {
	digitalWrite(pin, HIGH);
	state = true;
}
void SwitchByPin::turnOff() {
	digitalWrite(pin, LOW);
	state = false;
}
void SwitchByPin::turn(bool state) {
	if(state) turnOn();
	else      turnOff();
}

bool SwitchByPin::getState() {
	return state;
}
