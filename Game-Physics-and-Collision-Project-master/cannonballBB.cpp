#include "cannonballBB.h"
#include "GL\glew.h"
#include "Transform.h"
#include "GL\freeglut.h"
#include "math.h"
#include <iostream>
#include<glm\glm.hpp>
using namespace std;
using namespace glm;
float pi = 3.1415926535;


void cannonballBB::show(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	vec2 position = transform.getPosition();
	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (50.0f * width)) / (50.0f * width),
		(position.y - (50.0f * height)) / (50.0f * height), 0.0f);  // Translate to (xPos, yPos)

																  // Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 0.0);								// Cyan
	glVertex2f(0.0f, 0.0f);										// Center of circle
	int numSegments = 1000;
	float angle;
	for (int i = 0; i <= numSegments; i++) {					// Last vertex same as first vertex
		angle = i * 20.0f * pi / numSegments;			// 360 deg for all segments
		glVertex2f(cos(angle) * (20.0f * radius / width)* aspectRatio,
			sin(angle) * (20.0f * radius / height));
	}
	glEnd();
}
void cannonballBB::EulerSolver(float dt)
{
	
	move(radius + (dt * velocity));
	velocity = velocity + dt * acceleration;
	

}



void cannonballBB::move(vec2 traslation)
{
	std::cout << "inside move function" <<position.x << position.y<< std::endl;
	transform.Translate(traslation);
}

void cannonballBB::update(float dt) {

	EulerSolver(dt);
}

float cannonballBB::getRadius() {

	return radius;
}