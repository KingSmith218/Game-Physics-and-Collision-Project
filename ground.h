#pragma once
#include "Entity.h"

class ground : public Entity
{
public:

	void applygravity() {}
	void applypillargravity() {}
	void move(float angle) {}
	float getY() { float number = 0; return number; }
	float getSpeed() { float number = 0; return number; }
	void reduceSpeed() {}
	void update(float dt) {}

	ground(float ix, float iy);
	void show(int width, int height);
private:
	float x, y;
};
