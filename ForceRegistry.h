// (c) Marco Gilardi, 2017
#pragma once
#include "Parameters.h"
#include "PhysicsEntity.h"
#include "ForceGenerator.h"

#include <vector>
using namespace std;

class ForceRegistry
{
private:
	struct ForceRegistration
	{
		Parameters* params;
		ForceGenerator* force;

	};

	vector<ForceRegistration> registrations;
public:
	virtual ~ForceRegistry() {}
	void add(PhysicsEntity* obj, ForceGenerator* fg);
	void remove(PhysicsEntity* obj, ForceGenerator* fg);
	void clear();
	void updateForces(float dt);
};
