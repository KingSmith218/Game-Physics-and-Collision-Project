// (c) Marco Gilardi, 2017
#include "ForceRegistry.h"

void ForceRegistry::add(PhysicsEntity * obj, ForceGenerator* fg)
{
	ForceRegistration fr;
	fr.force = fg;
	fr.params = obj->getParams();
	registrations.push_back(fr);
}

void ForceRegistry::remove(PhysicsEntity * obj, ForceGenerator * fg)
{
	for (vector<ForceRegistration>::iterator it = registrations.begin(); it < registrations.end(); it++)
	{
		if (it->params == obj->getParams())
		{
			registrations.erase(it);
			break;
		}
	}
}

void ForceRegistry::clear()
{
	for (vector<ForceRegistration>::iterator it = registrations.begin(); it < registrations.end(); ++it)
	{
		it->params->clearAccumulator();
	}
}

void ForceRegistry::updateForces(float dt)
{
	for (vector<ForceRegistration>::iterator it = registrations.begin(); it < registrations.end(); ++it)
	{
		it->force->updateForce(it->params, dt);
	}
}