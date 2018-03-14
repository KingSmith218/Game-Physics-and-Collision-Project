// (c) Marco Gilardi, 2017
#pragma once
#include "Collider.h"
#include "Contact.h"
#include "glm\glm.hpp"

using namespace glm;

class AABB :public Collider
{
public:
	AABB(vec2& radii, const Transform& transform) :radii(radii), center(transform.getPosition()){};
	virtual ~AABB() {};
	void update(const Transform& transform);

	const vec2 getCenter() const;
	const vec2 getRadii() const;

private:
	vec2 radii;
	vec2 center;
	Collider* c;
};
