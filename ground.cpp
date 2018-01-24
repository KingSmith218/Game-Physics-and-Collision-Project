#include "ground.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

ground::ground(float ix, float iy) {
	x = ix;
	y = iy;
}

void ground::show(int width, int height) {
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.0);
	glLoadIdentity();
	glBegin(GL_POLYGON);
	glVertex2d(-750, -375); // floor top is -370, 
	glVertex2d(-750, -370);
	glVertex2d(750, -370);
	glVertex2d(750, -375);
	glEnd();

}