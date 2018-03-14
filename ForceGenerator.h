// (c) Marco Gilardi, 2017
#pragma once
#include "Parameters.h"

class ForceGenerator
{
public:
	virtual ~ForceGenerator() {}
	virtual void updateForce(Parameters* obj, float dt) = 0;
};
