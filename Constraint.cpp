 #include "Constraint.h"
 #include<glm\glm.hpp>
 using namespace glm;

void Constraint::solve(float dt)
{
	vec2 oldImpulse = impulse;
	vec2 delta = contact->computeImpulse(dt);
	impulse += delta;
	impulse = max(vec2(0), impulse);
	delta = impulse - oldImpulse;
	contact->applyImpulse(delta);
}