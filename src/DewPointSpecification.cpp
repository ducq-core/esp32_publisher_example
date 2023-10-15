#include "DewPointSpecification.hpp"

#include <stdio.h>

DewPointSpecification::DewPointSpecification(float threshold):
	threshold(threshold)
{}

bool DewPointSpecification::isSatisfiedBy(const Meteo *meteo) {
	return meteo->humidity > threshold;
}