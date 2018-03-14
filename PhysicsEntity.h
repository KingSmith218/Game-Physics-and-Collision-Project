// (c) Marco Gilardi, 2017
#pragma once
#include "Entity.h"
#include "Parameters.h"
#include "Collider.h"

class PhysicsEntity : public Entity
{
protected:
	Parameters* params = nullptr;
	Collider* collider = nullptr;

public:
	PhysicsEntity() {  }

	virtual ~PhysicsEntity() 
	{
		if (params != nullptr) delete params;
		if (collider != nullptr) delete collider;
	};

	virtual void update(float dt) = 0;
	virtual void draw(int width, int height) = 0;

	Parameters* getParams();
	void setParams(Parameters* params);

	Collider* getCollider();
};