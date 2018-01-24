#pragma once
#include <glm\glm.hpp>
#include "Entity.h"
#include "Transform.h"
#include <iostream>
class pillar : public Entity
{
public:
	//pillar(float ix, float iy);
	pillar(vec2 position, vec2 velocity, vec2 acceleration ) : position(position), velocity(velocity), acceleration(acceleration)
	{
		move(position);
	}
	void show(int width, int height);
	void applygravity() {}
	void applypillargravity();
	void stopGravity();
	void move(float angle);
    float getSpeed();
	float getX();
	float getY();
	float halfWidth();
	float halfHeight();
	void reduceSpeed();
	void update(float dt);


private:
	float x, y;
	float halfwidth = 15;
	float halfheight = 75;
    float GRAVITY = 0.3;
	bool isHorizontal;
    vec2 acceleration;
    vec2 velocity;
	vec2 position;
	Transform transform;
	void move(vec2 traslation);   
	void EulerSolver(float dt);
};