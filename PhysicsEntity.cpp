// (c) Marco Gilardi, 2017
#include "PhysicsEntity.h"

Parameters * PhysicsEntity::getParams()
{
	return params;
}

void PhysicsEntity::setParams(Parameters * params)
{
	PhysicsEntity::params = params;
}

Collider * PhysicsEntity::getCollider()
{
	return collider;
}