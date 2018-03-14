// (c) Marco Gilardi, 2017
#pragma once
#include "Parameters.h"
#include "PhysicsEntity.h"
#include <vector>

class Solver
{
private:
	virtual void solver(Parameters* params, float dt) = 0;
public:
	void integrate(vector<PhysicsEntity*>& dynObjs, float dt);
};