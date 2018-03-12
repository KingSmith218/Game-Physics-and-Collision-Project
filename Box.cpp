#include "Box.h"
#include <iostream>

using namespace std;

void Box::update(float dt)
{
	collider->update(params->transform);
}

void Box::draw(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	vec2 position = params->transform.getPosition();

	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

																  // Use triangular segments to form a circle
	glBegin(GL_QUADS);
	glColor3f(color.r, color.g, color.b);								// Yellow
	glVertex2f(2 * radii.x * aspectRatio / width, 2 * radii.y / height);
	glVertex2f(-2 * radii.x * aspectRatio / width, 2 * radii.y / height);
	glVertex2f(-2 * radii.x * aspectRatio / width, -2 * radii.y / height);
	glVertex2f(2 * radii.x * aspectRatio / width, -2 * radii.y / height);
	glEnd();
}
