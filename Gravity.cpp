// (c) Marco Gilardi, 2017
#include "Gravity.h"
#include "Parameters.h"

void Gravity::updateForce(Parameters* objParams, float dt)
{
	objParams->addForce(gravity*objParams->getMass());
}
