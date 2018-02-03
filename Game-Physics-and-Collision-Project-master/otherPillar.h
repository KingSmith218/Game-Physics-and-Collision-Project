#pragma once
#include "Entity.h"

class otherPillar : public Entity
{
public:
	otherPillar(float ix, float iy);
	void show(int width, int height);
	void applypillargravity();
	void applygravity() {}
	void stopGravity();
	void move(float angle);
	void reduceSpeed();
	float getSpeed();
	float getX();
	float getY();
	void update(float dt) {}
private:
	float x, y;
	float GRAVITY = 0.3;
};