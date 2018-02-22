#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>

#include "AABB.h"
#include "PhysicsEntity.h"

using namespace std;
using namespace glm;

class Cannon : public PhysicsEntity
{
private:
	vec2 radii;
	vec3 color;
	float angle = 0;
	float Power;

public:												// Yellow
	Cannon( vec2 r, Parameters* params, vec3 color = vec3(0, 1, 0)) : radii(r), color(color)
	{
		Cannon::params = params;
		collider = new AABB(radii, params->transform);
	}

	virtual ~Cannon() {
	}

	// move cannon around
	float getAngle() { return angle; }
	void setAngle(float newAngle) { angle += newAngle; }

	float getPower() { return Power; }
	void setPower(float newPower) { Power = newPower; }

	void update(float dt);

	void draw(int width, int height);
};