// (c) Marco Gilardi, 2017
#include "VerletSolver.h"

void VerletSolver::solver(Parameters* params, float dt)
{
	params->transform.Translate(dt*params->velocity + 0.5f * dt * dt * params->acceleration);
	params->velocity += 0.5f * dt *params->acceleration;
	params->acceleration = params->getResultant() * params->getInvMass();
	params->velocity += 0.5f * dt *params->acceleration;

}
