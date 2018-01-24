#include "GL\glew.h"
#include "GL\freeglut.h"
#include "math.h"
#include <vector>
#include <glm\glm.hpp>
#include <Windows.h>
#include "cannon.h"
#include "ground.h"
#include "pillar.h"
#include "otherPillar.h"
#include "cannonballBB.h"
#include "GameWindow.h"
#include <iostream>

using namespace std;
using namespace glm;


int followAngle = 270;
int pressedAngle = 270;
int score = 0;
bool stopped = false;
bool hasinitialised = false;
bool cancelGravity = false;
bool added = false;
cannon c1(0, 0);
cannonballBB* cannonballBB1 = new cannonballBB(1000, vec2(-5470000.5,-290), vec2(10000, 10000), vec2(100, 100)); // fix aspect ratio to put in correct place
std::vector<Entity*> gameEntities;

bool PillarOtherPillarCollision(pillar& p1, otherPillar& p2)
{
	float X1 = 0, X2 = 30, Y1 = 0, Y2 = 150;
	float oX1 = 0, oX2 = 150, oY1 = 0, oY2 = 30;

	if (p1.getX() + X1 < p2.getX() + oX2 && p1.getX() + X2 > p2.getX() + oX1 &&
		p1.getY() + Y1 < p2.getY() + oY2 && p1.getY() + Y2 > p2.getY() + oY1)  {

		return true;
	}
	else {
		
		return false;
		
	}
}

  bool GroundPillarCollision(ground& g1, pillar& p1) {

	  if (p1.getY() <= -355) {
		  return true;
	  }
	  else {
		  return false;
	  }
}
  /*
bool BallGroundCollision(ground&  b1, cannonballBB&  b2)
{
	if (b2.getY() <= -370) {
		return true;
	}
	else {
		return false;
	}
}
*/
bool PillarPillarCollision(pillar& p1, pillar& p2)
{
		float X1 = 0, X2 = 30, Y1 = 0, Y2 = 150;

	if (p1.getX() + X1 < p2.getX() + X2 && p1.getX() + X2 > p2.getX() + X1 &&
		p1.getY() + Y1 < p2.getY() + Y2 && p1.getY() + Y2 > p2.getY() + Y1) {

		return true;
	}
	else {
		return false;
	}
	
}

void CheckCollisions()
{
	for (std::vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end() - 1; it++) 
	{
		pillar* pillar1 = dynamic_cast<pillar*> (*it); 
		if (pillar1 != nullptr) 
		{
			for (std::vector<Entity*>::iterator it1 = it + 1; it1 < gameEntities.end(); it1++) 
			{
				otherPillar* otherpillar1 = dynamic_cast<otherPillar*> (*it1); 
				if (otherpillar1 != nullptr) 
				{
					
					if (PillarOtherPillarCollision(*pillar1, *otherpillar1))
					{
						otherpillar1->stopGravity();
						pillar1->stopGravity();
					}
				}
				pillar* pillar2 = dynamic_cast<pillar*> (*it1); 
				if (pillar2 != nullptr) 
				{
					
					if (PillarPillarCollision(*pillar1, *pillar2))
					{
						pillar1->stopGravity();
						pillar2->stopGravity();
					}
				}

				ground* ground1 = dynamic_cast<ground*> (*it1);
				if (ground1 != nullptr)
				{
					cout << "ground exists" << endl;
					if (GroundPillarCollision(*ground1, *pillar1))
					{
						std::cout << "ball has hit a pillar" << std::endl;

					}
				}


				/* put if statement for ball collision here/*
				cannonballBB* ball1 = dynamic_cast<cannonballBB*> (*it1); 
				if (ball1 != nullptr) 
				{
					if (BallPillarCollision(*ball1, *pillar1))
					{
						std::cout << "ball has hit a pillar" << std::endl;
						
					}
				}
				
				
				ground* ground1 = dynamic_cast<ground*> (*it1);   //////// not acknowledging existence 
				if (ground1 != nullptr) 
				{
					cout << "acknowledges ground exists" << endl;
				if (BallGroundCollision(*ground1, *ball1))
				{
					std::cout << "ball has hit the ground" << std::endl;
				
		 	}
				}
			*/
			
			}
			
		}
	}
}

void clearBall(int value) {
	added = false;
	stopped = false;
	// delete ball
}

void reset(int value) {

	/*
	for (std::vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end(); it++) {
	
		cannonballBB* cannonballBB1 = dynamic_cast<cannonballBB*> (*it);
		if (cannonballBB1 != nullptr)
		{
			float cannonSpeed = (*it)->getSpeed();
			int yvalue = (*it)->getY();
			if (cannonSpeed > 0) {
				(*it)->reduceSpeed();
			}
			if (cannonSpeed <= 0 && yvalue > -355) {

				stopped = true;
			}
			if (cannonSpeed <= 0 && yvalue <= -355) {
				if (stopped == true) {
					glutTimerFunc(3000, clearBall, 0);	
					call timer to delete ball

				}
				else {
					added = false;
					delete ball
					
				}
			}

		}
	}

	*/

}

void special_keys(int key, int x, int y)
{
	
	switch (key)
	{
	case GLUT_KEY_RIGHT:	

		if (followAngle != 180) {
			c1.move(-5);
			followAngle -= 5;
		}
		break;

	case GLUT_KEY_LEFT:

		if (followAngle != 360) {
			c1.move(5);
			followAngle += 5;
		}
		break;

	}
}

void renderbitmap(float x, float y, void *font, char *string) {

	char *c;
	glRasterPos2f(x, y);
		for (c = string; *c != '\0'; c++) {
			glutBitmapCharacter(font, *c);
		}
}

void stringfunction() {

	glColor3f(1.0f, 0.0f, 0.0f);
	char buf[100] = { 0 };
	sprintf_s(buf, " Score: "+score);
	renderbitmap(-750, 350, GLUT_BITMAP_TIMES_ROMAN_24, buf);

}
void update() {

	float dt = 1;
	for (vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end(); it++)
	{
		(*it)->update(dt);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	if(hasinitialised == false){

		ground* ground1 = new ground(0, 0);
		gameEntities.push_back(ground1);

		pillar* pillar1 = new pillar(vec2(100, 0), vec2(100, 0), vec2(10, 0));
		gameEntities.push_back(pillar1);
		
		/*
		pillar* pillar2 = new  pillar(-30, -20);
		gameEntities.push_back(pillar2);

		pillar* pillar3 = new  pillar( -150, 370);
		gameEntities.push_back(pillar3);

		pillar* pillar4 = new  pillar(50, 150);
		gameEntities.push_back(pillar4);

		pillar* pillar4a = new  pillar(50, 320);
		gameEntities.push_back(pillar4a);

		pillar* pillar5 = new  pillar(170, -20);
		gameEntities.push_back(pillar5);

		pillar* pillar6 = new  pillar(170, 150);
		gameEntities.push_back(pillar6);

		pillar* pillar7 = new  pillar(250, -20);
		gameEntities.push_back(pillar7);

		pillar* pillar8 = new  pillar(370, -20);
		gameEntities.push_back(pillar8);

		pillar* pillar9 = new  pillar(490, -20);
		gameEntities.push_back(pillar9);

		pillar* pillar10 = new  pillar(280, 200);
		gameEntities.push_back(pillar10);

		pillar* pillar11 = new  pillar(460, 200);
		gameEntities.push_back(pillar11);

		otherPillar* otherpillar1 = new otherPillar(-150, 150);
		gameEntities.push_back(otherpillar1);
		
		otherPillar* otherpillar2 = new otherPillar(385, 150);
		gameEntities.push_back(otherpillar2);

		otherPillar* otherpillar3 = new otherPillar(235, 150);
		gameEntities.push_back(otherpillar3);
		*/
		hasinitialised = true;
	}

	if (GetKeyState('A') & 0x8000)
	{
		
		if (added == false) {
			pressedAngle = followAngle;
			gameEntities.push_back(cannonballBB1);
			glutTimerFunc(300, reset, 0);
			added = true;
		}
	}
	
		for (std::vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end(); it++)
			{
					(*it)->show(1500, 750); // draw all existing entities
			}

	c1.show();
	c1.show_cannon();
	stringfunction();
	CheckCollisions();
	glutSwapBuffers();
	glutPostRedisplay();
}




int main(int argc, char** argv)
{
	int width = 1500;
	int height = 750;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(width, height);
	glutCreateWindow("Game Physics project");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1.0, 1.0);
	glutSpecialFunc(special_keys);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutMainLoop();
}

