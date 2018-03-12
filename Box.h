
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>
#include "AABB.h"
#include "PhysicsEntity.h"

using namespace std;
using namespace glm;

class Box : public PhysicsEntity
{
private:
	vec2 radii;
	vec3 color;

public:												// Yellow
	Box(vec2 r, Parameters* params, vec3 color = vec3( 1, 1, 0)) : radii(r), color(color)
	{
		Box::params = params;
		collider = new AABB(radii, params->transform);
	}

	virtual ~Box() {
	}

	void update(float dt);

	void draw(int width, int height);
};