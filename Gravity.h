// (c) Marco Gilardi, 2017
#pragma once
#include <glm\glm.hpp>
#include "Parameters.h"
#include "ForceGenerator.h"

class Gravity : public ForceGenerator
{
private:
	vec2 gravity;

public:
	Gravity(const vec2& gravity) :gravity(gravity) {}
	virtual ~Gravity() {}
	void updateForce(Parameters* objParams, float dt);
};
