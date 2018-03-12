// (c) Marco Gilardi, 2017
#include "EulerSolver.h"

void EulerSolver::solver(Parameters* params, float dt)
{
	params->transform.Translate(dt * params->velocity);
	params->velocity += dt * params->acceleration;
	params->acceleration = params->getResultant() * params->getInvMass();
}