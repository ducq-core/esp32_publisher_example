#pragma once



class ISinkSwitch {
public:
	virtual void save(bool isOn) = 0;
};