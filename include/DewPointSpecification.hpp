#pragma once

#include "IMeteoSpecification.hpp"

class DewPointSpecification: public IMeteoSpecification {
private:
	float threshold;
public:
	DewPointSpecification(float threshold);
	bool isSatisfiedBy(const Meteo *meteo) override;
};