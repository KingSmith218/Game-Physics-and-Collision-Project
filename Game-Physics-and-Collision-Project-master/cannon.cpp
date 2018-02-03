#include "cannon.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

cannon::cannon(float ix, float iy) {

	x = ix;
	y = iy;

}

void cannon::move(float Aangle) {

	angle += Aangle;
}

void cannon::show() {

	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(-745, -370);
	glVertex2d(-745, -340);
	glVertex2d(-350, -340);
	glVertex2d(-350, -370);
	glEnd();

	glColor3f(0.0, 0.0, 0.5);
	glBegin(GL_POLYGON);
	glVertex2d(-745, -350);
	glVertex2d(-745, -340);
	glVertex2d(-350, -340);
	glVertex2d(-350, -350);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(-645, -280);
	glVertex2d(-645, -340);
	glVertex2d(-450, -340);
	glVertex2d(-450, -280);
	glVertex2d(-500, -250);
	glVertex2d(-595, -250);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(-640, -280);
	glVertex2d(-640, -335);
	glVertex2d(-455, -335);
	glVertex2d(-455, -280);
	glVertex2d(-500, -255);
	glVertex2d(-595, -255);
	glEnd();
	glPopMatrix();
}

void cannon::show_cannon() {
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.8);
	glTranslatef(-547.5, -297.5, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(547.5, 297.5, 0);
	glBegin(GL_POLYGON);
	glVertex2d(-575, -150);
	glVertex2d(-520, -150);
	glVertex2d(-520, -270);
	glVertex2d(-545, -300);
	glVertex2d(-550, -300);
	glVertex2d(-575, -270);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(-570, -155);
	glVertex2d(-525, -155);
	glVertex2d(-525, -270); 
	glVertex2d(-570, -270);
	glEnd();
	glPopMatrix();
	
}
