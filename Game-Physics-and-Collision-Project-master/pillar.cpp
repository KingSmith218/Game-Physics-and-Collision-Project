#include "pillar.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "Transform.h"
#include <iostream>

void pillar::move(float angle) {}
void pillar::reduceSpeed() {}
float pillar::getSpeed() {float number = 0; return number;}

void pillar::applypillargravity() {

	if (y > -370) {
		y -= GRAVITY;
	}

}

void pillar::show(int width, int height) {



	vec2 position = transform.getPosition();
	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (50.0f * width)) / (50.0f * width),
		(position.y - (50.0f * height)) / (50.0f * height), 0.0f);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(position.x * (20.0f / width)* aspectRatio,   position.y * (20.0f  / height));
	glVertex2f(position.x * (40.0f / width)* aspectRatio, position.y * (40.0f / height));
	glEnd();
	/*
		glBegin(GL_POLYGON);
		glVertex2d((position.x)/** aspectRatio, (position.y + 150));  //// need to fix this to make it appear
		glVertex2d((position.x +30)/** aspectRatio, (position.y + 150) );
		glVertex2d((position.x +30)/** aspectRatio, (position.y) );
		glVertex2d((x)/** aspectRatio, (y) );
		glEnd();
		*/
		
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(position.x + 2 / width * aspectRatio, position.y + 148 / height);
        glVertex2d(position.x + 28 / width * aspectRatio, position.y + 148 / height);
		glVertex2d(position.x + 28 / width * aspectRatio, position.y + 2 / height);
		glVertex2d(position.x + 2 / width * aspectRatio, position.y + 2 / height);
		glEnd();
		glPopMatrix();

}
/*
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
*/
float pillar::getX() {

	return x;
}

float pillar::getY() {

	return y;
}

void pillar::stopGravity() {

	GRAVITY = 0;
}

float pillar::halfWidth() {

	return halfwidth;
}

float pillar::halfHeight() {

	return halfheight;
}

void pillar::EulerSolver(float dt)
{
	//vec2 position(halfwidth, halfheight);
	//move(position + (dt * velocity));
	//velocity = velocity + dt * acceleration;


}



void pillar::move(vec2 traslation)
{
	//std::cout << "inside move function" << position.x << position.y << std::endl;
	transform.Translate(traslation);
}

void pillar::update(float dt) {

	EulerSolver(dt);
}
