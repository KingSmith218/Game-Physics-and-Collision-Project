// (c) Marco Gilardi, 2017
#include "Ball.h"
#include <iostream>

using namespace std;

void Ball::update(float dt)
{
	collider->update(params->transform);
}

void Ball::setAngle(float newAngle)
{
	angle = newAngle;
	//params->setVelocity(length(params->velocity) * vec2(std::cos(newAngle), std::sin(newAngle))); 
}


void Ball::draw(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	vec2 position = params->transform.getPosition();

	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);

	glTranslatef(aspectRatio * ( position.x - (0.5f * width)) / (0.5f * width),
		( position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

	//glTranslatef(cos(angle - 90 * (M_PI / 180)), sin(angle - 90 * (M_PI / 180)), 0.0f);

	// Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(0.0f, 0.0f);										// Center of circle
	int numSegments = 100;

	for (int i = 0; i <= numSegments; i++) {					// Last vertex same as first vertex
		angle = i * 2.0f * pi<float>()/ numSegments;			// 360 deg for all segments
		glVertex2f(cos(angle)* (2.0f * radius / width)* aspectRatio,
			sin(angle)* (2.0f * radius / height));
		
	}
	glEnd();
}
