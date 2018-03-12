#pragma once
#include "PhysicsEntity.h"
#include "Contact.h"

class Constraint {
protected:
	friend Contact;
public:
	vec2 impulse;
	Contact* contact;
	
	void solve(float dt);
};
