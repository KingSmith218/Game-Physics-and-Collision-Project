// (c) Marco Gilardi, 2017
#include "Parameters.h"
#include <assert.h>
#include <limits>
void Parameters::setInvMass(float mass)
{
	if (mass > 0)
		inverseMass = 1 / mass;
	else
		inverseMass = 0;
}

float Parameters::getInvMass()
{
	return inverseMass;
}

float Parameters::getMass()
{
	if (inverseMass == 0)
		return FLT_MAX;
	else
		return 1.0f/inverseMass;
}

void Parameters::setVelocity(vec2 v)
{
	velocity = v;
}

void Parameters::setRestitution(float rest)
{
	restitution = Utils::clamp(rest);
}

float Parameters::getRestitution()
{
	return restitution;
}

vec2 Parameters::getResultant()
{
	return forceAccum;
}

void Parameters::clearAccumulator()
{
	forceAccum = vec2(0);
}

void Parameters::addForce(vec2& force)
{
	forceAccum += force;
}
