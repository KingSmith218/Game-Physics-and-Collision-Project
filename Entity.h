// (c) Marco Gilardi, 2017
#pragma once
#include <glm\glm.hpp>
using namespace glm;

class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(int width, int height) = 0;
};
