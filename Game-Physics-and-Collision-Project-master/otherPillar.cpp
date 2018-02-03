#include "otherPillar.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

otherPillar::otherPillar(float ix, float iy) {

	x = ix;
	y = iy;

}

void otherPillar::move(float angle) {}
void otherPillar::reduceSpeed() {}
float otherPillar::getSpeed() {	float number = 0; return number;}

void otherPillar::applypillargravity() {

	if (y > -370) {
		y -= GRAVITY;
	}

}

void otherPillar::show(int width, int height) {

	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x , y + 30);
	glVertex2d(x + 150, y + 30);
	glVertex2d(x + 150, y);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(x + 2, y + 2);  
	glVertex2d(x + 2, y + 28);
	glVertex2d(x + 148, y + 28);
	glVertex2d(x + 148, y + 2);
	glEnd();
	glPopMatrix();

}

float otherPillar::getX() {

	return x;
}

float otherPillar::getY() {

	return y;
}

void otherPillar::stopGravity() {

	GRAVITY = 0;
}