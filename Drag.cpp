#include "Drag.h"
#include <glm\glm.hpp>
using namespace glm;

void Drag::updateForce(Parameters * params, float dt)
{
	vec2 drag = params->velocity;
	float dragCoeff = length(drag);
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff*dragCoeff;
	if(length(drag)!=0)
	drag = -dragCoeff * normalize(drag);
	params->addForce(drag);
}
