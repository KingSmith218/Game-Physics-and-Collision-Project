#pragma once

class Entity
{
public:
	virtual void show(int width, int height) = 0;
	virtual void update(float dt) = 0;
//	virtual float getY() = 0;

}; 
