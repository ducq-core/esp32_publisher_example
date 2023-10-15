#pragma once


class ISwitch {

public:
	static const bool ON  = true;
	static const bool OFF = false;

	virtual void turnOn() = 0;
	virtual void turnOff() = 0;
	virtual void turn(bool state) = 0;
	virtual bool getState() = 0;
};