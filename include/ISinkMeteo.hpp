#pragma once

#include "MeteoValueObject.hpp"

class ISinkMeteo {
public:
	virtual void save(Meteo *meteo) = 0;
};