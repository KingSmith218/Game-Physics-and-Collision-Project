// (c) Marco Gilardi, 2017
#include "Game.h"
#include "EulerSolver.h"
#include "VerletSolver.h"
#include "Ball.h"
#include "Box.h"
#include "Gravity.h"
#include "CollisionDetector.h"
#include "Drag.h"
#include "Cannon.h"
#include <Windows.h>
#include <iostream>

#define SPACEBAR 32
using namespace std;

bool shoot;
bool shot = false;

void Game::Load()
{
	window = new GameWindow("Cannon Shooter project", 1450, 750, 0, 0); // create new window at 0,0 size 1450 x 750

	solver = new VerletSolver(); // verlet solver mimimises the vibrating motion

	forceRegistry = new ForceRegistry();
	resolver = new ContactResolver();

	gravity = new Gravity(vec2(0, -300)); // apply downward gravity on everything
    drag = new Drag(0.05f, 0.05f);

		// parameters are mass, position, initial velocity and restitution
		/*params = new Parameters(20, vec2(100, 255), vec2(0), .0f); //Top Resting circle - Try setting this circle heavier than the others, a limit of the current approach stacking of objects vibrate ..... parameters just to shorten creation code
		ball = new  Ball(20, params); //Radius set equal to the mass, so that the circle grows in size as the mass incerases
		forceRegistry->add(ball, gravity); // allow gravity to act on ball
		forceRegistry->add(ball, drag);   // allow drag to act on ball
		dynObjs.push_back(ball);          // add to vector

		params = new Parameters(10, vec2(100, 220), vec2(0), .0f); //Middle Resting circle
		ball = new  Ball(10.0f, params);
		forceRegistry->add(ball, gravity);
		forceRegistry->add(ball, drag);
		dynObjs.push_back(ball);

		params = new Parameters(10, vec2(100, 200), vec2(0), .0f); //Middle Resting circle
		ball = new  Ball(10.0f, params);
		forceRegistry->add(ball, gravity);
		forceRegistry->add(ball, drag);
		dynObjs.push_back(ball);

		params = new Parameters(0, vec2(100, 180), vec2(0), .0f); //Fixed Object
		ball = new  Ball(10.0f, params, vec3(0.0f, 1.0f, 0.0f));
		dynObjs.push_back(ball);
		*/
		// object is fixed because it is not added to gravity and drag force registry

		params = new Parameters(200, vec2(400, 240), vec2(0), 0.75f); //Falling Box.... make into pillar
		boxVert = new  Box(vec2(15, 70), params, vec3(1, 0, 1));
		forceRegistry->add(boxVert, gravity); // only gravity, no drag affecting 
		forceRegistry->add(boxVert, drag); // until now
		dynObjs.push_back(boxVert);
		
		params = new Parameters(200, vec2(400, 350), vec2(0), 0.75f); //Falling Box.... make into pillar .... horizontal pillar
		horizontalBox = new  Box(vec2(70, 15), params, vec3(1, 0, 1));
		forceRegistry->add(horizontalBox, gravity); // only gravity, no drag affecting 
		forceRegistry->add(horizontalBox, drag); // until now
		dynObjs.push_back(horizontalBox);
		
		params = new Parameters(200, vec2(150, 57.5), vec2(0), 0.75f); //Falling Box.... try making into stationary cannon
		cannon = new  Cannon(vec2(60, 30), params, vec3(0.3, 0.3, 0.3));
		
		params = new Parameters(0, vec2(350, 10), vec2(0)); //Ground
		box = new  Box(vec2(1450, 10), params, vec3(0, 1, 0));
		dynObjs.push_back(box);

		params = new Parameters(0, vec2(10, 10), vec2(0)); //Left Wall
		box = new  Box(vec2(20, 440), params, vec3(0.3, 0.3, 0.3));
		dynObjs.push_back(box);

		params = new Parameters(0, vec2(1435, 10), vec2(0)); //Right Wall 
		box = new  Box(vec2(20, 440), params, vec3(0.3, 0.3, 0.3));
		dynObjs.push_back(box);
	

}

void Game::GetCollisionsData()
{
	for (vector<PhysicsEntity*>::iterator it_obj1 = dynObjs.begin(); it_obj1 < dynObjs.end() - 1; it_obj1++) // cycle through all objects
	{
		for (vector<PhysicsEntity*>::iterator it_obj2 = it_obj1 + 1; it_obj2 < dynObjs.end(); it_obj2++) // only checking same object collisions once
		{
			
			CollisionData * data = CollisionDetector::CheckCollision(*it_obj1, *it_obj2); // create collision test and call it
			if(data!=nullptr)
				collisionData.push_back(unique_ptr<CollisionData>(data));
		}
	}
}
bool pressedDown = false;


void Game::SpecialKeys( int key, int x, int y)
{
	
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		cannon->setAngle(-2.5);
		break;

	case GLUT_KEY_LEFT:
		cannon->setAngle(2.5);

		break;
	}
}
void Game::keysUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case SPACEBAR:

		if (shoot == false) {       // if reset function has been called or game has just been initialised
			shoot = true;           // call function in update to create a new object
		}
		break;
	}
}


 void Reset(int value)
{
	cout << "called" << endl;
	shoot = false;
	shot = false;
}


void Game::Update(float dt)
{	
	

	GetCollisionsData();			//Check for colliison

	while (!collisionData.empty())
	{
		unique_ptr<CollisionData>& data = collisionData.back();
		resolver->setNumIterations(data->maxNumContacts - data->numContactsLeft);
		if (data->contact != nullptr)
			resolver->resolveContacts(data->contact, data->maxNumContacts, dt);
				params = new Parameters(10, vec2(0, 0), vec2(0)); //Ground          // work out how to calculate contact point, how to do warm starting, object shattering, also where to calculate angular velocity and implement it
				box = new  Box(vec2(5, 5), params, vec3(0, 1, 0));
				contactPoints.push_back(box);
		collisionData.pop_back(); //remove the last element from the vector, being it a smart pointer delete is called automatically on it
	}
	

   float angle = cannon->getAngle();
	             cannon->setPower(power);


	if (GetAsyncKeyState(VK_SPACE) & 0x80000000)
	{

		if (shoot == false) {
			if (power < 2000) {
				power = power + 10;
			}
		}

	}


	if (shoot == true)
	{
		if (shot == false) {

			params = new Parameters(20, vec2(150, 75), vec2(power*std::sin(-3.14*angle/180.0), power*std::cos(-3.14*angle/180)), .0f); // 1000 increases power, make variable for changing power level
			ball = new  Ball(7.0f, params, vec3(0, 1, 0));
			ball->setAngle(angle);
			forceRegistry->add(ball, gravity);  
			forceRegistry->add(ball, drag);
			
			/*
			PhysicsEntity* wallR = dynObjs[dynObjs.size() - 1];
			dynObjs.pop_back();
			PhysicsEntity* wallL = dynObjs[dynObjs.size() - 1];
			dynObjs.pop_back();
			PhysicsEntity* Ground = dynObjs[dynObjs.size() - 1];
			dynObjs.pop_back();
			
			dynObjs.push_back(ball);
			dynObjs.push_back(Ground);
			dynObjs.push_back(wallL);
			dynObjs.push_back(wallR);
			*/

			dynObjs.insert(dynObjs.begin(), ball);

			power = 300;
			glutTimerFunc(5000, Reset, 1);

			
		}
		shot = true;
	}

	forceRegistry->updateForces(dt); //Update forces and computes their resultant
	solver->integrate(dynObjs, dt); //Updates Position, Velocity and Acceleration of each object
	forceRegistry->clear();			 //Set the resultant of the forces of each object to 0

	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
	{

		(*it)->update(dt);			//Updates other quantities in each object
	
	}
	cannon->update(dt);             // update cannon seperate from vector
}

void Game::ReshapeWindow(int width, int height)
{
	window->Reshape(width, height); // maximising causes problems
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix

	cannon->draw(window->getWidth(), window->getHeight()); // draw cannon seperate from vector
	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
	{
		(*it)->draw(window->getWidth(), window->getHeight());
	}

	for (vector<Box*>::iterator it = contactPoints.begin(); it < contactPoints.end(); it++)
	{
		(*it)->draw(window->getWidth(), window->getHeight());
	}

	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}

void Game::Inputs()
{
}






