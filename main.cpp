#include <GL\glut.h> 

#include "Game.h"
#include "Timer.h"

const int refreshMillis = 16;      // Refresh period in milliseconds

Game* game;
LowResTimer timer;			// Not ideal for games but for a demo is OK-ish
double oldTime = 0;

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0, 0.0, 0.5, 1.0); // Set background (clear) color to black
}



/* Callback handler for window re-paint event */
void display() {

	game->Render();
}

/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) 
{
	game->ReshapeWindow(width, height);
}

void SpecialKeys(int key, int x, int y)
{
	game->SpecialKeys(key, x, y);
}

void keysUp(unsigned char key, int x, int y)
{
	game->keysUp(key, x, y);
}
/* Fixed Time Update */
void update(int value) 
{
	game->Update(timer.getTime()-oldTime);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardUpFunc(keysUp);

	glutPostRedisplay();						// Post a paint request to activate display()
	glutTimerFunc(refreshMillis, update, 0);	// Subsequent timer call at milliseconds
	oldTime = timer.getTime();
}

void GLUTRenderer()
{
	glutDisplayFunc(display);		// Register callback handler for window re-paint
	glutReshapeFunc(reshape);		// Register callback handler for window re-shape
	glutTimerFunc(0, update, 0);	// First timer call immediately
	initGL();						// Our own OpenGL initialization
	glutMainLoop();					// Enter event-processing loop
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	game = new Game();
	game->Load();
	timer.startTimer();
	GLUTRenderer();

	delete game;

	return 0;
}