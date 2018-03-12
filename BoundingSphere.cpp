// (c) Marco Gilardi, 2017
#include "BoundingSphere.h"
#include "AABB.h"
#include "CollisionDetector.h"
#include <iostream>
using namespace std;

/*
vector<vec2> BoundingSphere::computeContactPoints() const
{
	vector<vec2> contactPoints;
	vec2 direction = center - c->getCenter();
	contactPoints.push_back(center + radii * direction);
	return contactPoints;
}
vec2 BoundingSphere::computeContactNormal() const
{
	return normalize(center - c->getCenter());
}
*/

float BoundingSphere::getRadii() const
{
	return radius;
}

const vec2 BoundingSphere::getCenter() const
{
	return center;
}

void BoundingSphere::update(const Transform& transform)
{
	center = transform.getPosition();
}
