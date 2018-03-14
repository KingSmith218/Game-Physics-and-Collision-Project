// (c) Marco Gilardi, 2017
#pragma once
#include <GL\glut.h>
#include <memory>
#include "GameWindow.h"
#include "ForceRegistry.h"
#include "Solver.h"
#include "ContactResolver.h"
#include "CollisionData.h"
#include "Cannon.h"
#include "Gravity.h"
#include "Drag.h"
#include "Parameters.h"
#include "Ball.h"
#include "Box.h"
class Game
{
public:

	Cannon * cannon; // = nullptr;

	void Load();
	void Render();
	void Inputs();
	void Update(float dt);

	void ReshapeWindow(int weigth, int height);

	void SpecialKeys(int key, int x, int y);
	void keysUp(unsigned char key, int x, int y);

	//void Reset(int value);

	Game() {};
	virtual ~Game() 
	{
		if (solver != nullptr) delete solver;
		if (params != nullptr) delete params;
		if (gravity != nullptr) delete gravity;
		if (drag != nullptr) delete drag;
		if (window != nullptr) delete window; 
		if (forceRegistry != nullptr) delete forceRegistry;
		if (resolver != nullptr) delete resolver;

		for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
			delete *it;
	}

private:
	vector<unique_ptr<CollisionData>> collisionData; //Vector of smart pointers (http://umich.edu/~eecs381/handouts/C++11_smart_ptrs.pdf)
	vector<PhysicsEntity*> dynObjs;
	vector<Box*>contactPoints;
	ForceRegistry* forceRegistry = nullptr;
	Gravity* gravity = nullptr;
	Drag* drag = nullptr;
	ContactResolver* resolver = nullptr;
	Contact* contacts;
	Solver* solver = nullptr;
	Parameters* params = nullptr;
	GameWindow* window = nullptr;
	Ball* ball = nullptr;
	Box* box = nullptr;
	Box* boxVert = nullptr;
	Box* horizontalBox = nullptr;
	void GetCollisionsData();
	float newAngle = 0;
	float power = 300;
};