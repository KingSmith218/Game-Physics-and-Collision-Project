// (c) Marco Gilardi, 2017
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>

#include "BoundingSphere.h"
#include "PhysicsEntity.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace glm;

class Ball: public PhysicsEntity
{
private:
	float radius;
	vec3 color;
	float angle;
public:												// Cyan
	Ball(float radius, Parameters* params, vec3 color = vec3(0,1,1)) : radius(radius), color(color)
	{
		Ball::params = params;
		collider = new BoundingSphere(Ball::radius, params->transform.getPosition());
	}

	virtual ~Ball() { 
	}
	
	void setAngle(float newAngle);


	void update(float dt);

	void draw(int width, int height);
};