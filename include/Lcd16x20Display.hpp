#pragma once


#include "IDisplayMeteo.hpp"
#include "IDisplayStatus.hpp"

#include <LiquidCrystal_I2C.h>



class Lcd16x20Display: public IDisplayStatus, public IDisplayMeteo {
private:
	LiquidCrystal_I2C lcd;

public:
	Lcd16x20Display(int I2cAddr);

	void display(const char *message) override;
	void display(Meteo *meteo) override;
};