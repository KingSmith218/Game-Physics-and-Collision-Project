#include "Cannon.h"
#include <iostream>

using namespace std;

void Cannon::update(float dt)
{
	collider->update(params->transform);
}

void renderbitmap(float x, float y, void *font, char *string) {

	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


void Cannon::draw(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	vec2 position = params->transform.getPosition();

	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)



	glColor3f(1.0, 0.5, 0.0); // cannon base coloured part
	glBegin(GL_POLYGON);
	glVertex2f(1.5 * radii.x * aspectRatio / width, 2 * radii.y / height);
	glVertex2f(-1.5 * radii.x * aspectRatio / width, 2* radii.y / height);
	glVertex2f(-2.5 * radii.x * aspectRatio / width,- 2.5 * radii.y / height);
	glVertex2f(2.5 * radii.x * aspectRatio / width, -2.5* radii.y / height);
	glEnd();

	glColor3f(0.0, 0.0, 0.5); // and uncoloured part to make it appear to have a skeletal structure
	glBegin(GL_POLYGON);
	glVertex2f(1.40 * radii.x * aspectRatio / width, 1.65 * radii.y / height);
	glVertex2f(-1.40 * radii.x * aspectRatio / width, 1.65 * radii.y / height);
	glVertex2f(-2.25 * radii.x * aspectRatio / width, -2.25 * radii.y / height);
	glVertex2f(2.25* radii.x * aspectRatio / width, -2.25* radii.y / height);
	glEnd();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	char buf[100] = { 0 };
	sprintf_s(buf, "%s%.0f", "Power Level = " , Power);
	renderbitmap(-5.0*radii.x*aspectRatio / width, 44.0*radii.y / height, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glRotatef(angle, 0, 0, 1);
	glColor3f(1.0, 0.5, 0.0);   // rotating cannon piece (with colour)
	glBegin(GL_POLYGON);
	glVertex2f(0.55 * radii.x * aspectRatio / width, 8.0 * radii.y / height);
	glVertex2f(-0.55 * radii.x * aspectRatio / width, 8.0 * radii.y / height);
	glVertex2f(-0.55 * radii.x * aspectRatio / width, -0.3 * radii.y / height);
	glVertex2f(0.55* radii.x * aspectRatio / width, -0.3* radii.y / height);
	glEnd();

	float powerColour = Power / 2000;
	glColor3f(powerColour, 0.0, 0.5);   // rotating cannon piece (without colour)
	glBegin(GL_POLYGON);
	glVertex2f(0.45 * radii.x * aspectRatio / width, 7.9 * radii.y / height);
	glVertex2f(-0.45 * radii.x * aspectRatio / width, 7.9 * radii.y / height);
	glVertex2f(-0.45 * radii.x * aspectRatio / width, -0.2 * radii.y / height);
	glVertex2f(0.45* radii.x * aspectRatio / width, -0.2* radii.y / height);
	glEnd();


}

