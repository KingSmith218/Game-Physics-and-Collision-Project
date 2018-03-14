#pragma once
#include "ForceGenerator.h"
#include "PhysicsEntity.h"

class Drag : public ForceGenerator
{
private:
	float k1;
	float k2;
public:
	Drag(float k1, float k2) :k1(k1), k2(k2) {}
	virtual ~Drag() {}
	void updateForce(Parameters* obj, float dt);
};
