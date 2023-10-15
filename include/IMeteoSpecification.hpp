#pragma once

#include "MeteoValueObject.hpp"

class IMeteoSpecification {
public:
	virtual bool isSatisfiedBy(const Meteo *meteo) = 0;
};