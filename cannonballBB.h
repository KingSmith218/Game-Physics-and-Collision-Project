#pragma once
#include "Entity.h"
#include "Transform.h"
#include <iostream>

class cannonballBB : public Entity
{
public:
	cannonballBB(float r, vec2 pos, vec2 vel, vec2 acc) : radius(r), velocity(vel), acceleration(acc)
	{
		std::cout << "created" << std::endl;
		move(pos);
	}

	virtual ~cannonballBB() {}
	void update(float dt);
	float getRadius();
	void show(int width, int height);
	void show() {}
	void applypillargravity() {}

private:

	Transform transform;
	vec2 velocity;
	vec2 acceleration;
	vec2 position;
	void EulerSolver(float dt);
	void move(vec2 traslation);
	float radius;
	




};
