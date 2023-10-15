#pragma once

#include "MeteoValueObject.hpp"


class IDisplayMeteo {
public:
	virtual void display(Meteo *meteo) = 0;
};