// (c) Marco Gilardi, 2017
#include "Solver.h"

void Solver::integrate(vector<PhysicsEntity*>& dynObjs, float dt)
{
	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
	{
		solver((*it)->getParams(), dt);
	}
}
