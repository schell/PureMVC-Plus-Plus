#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <GLUT/glut.h>

#include "../../src/pmvcpp.h"

using namespace std;
using namespace PureMVC;

/**
 *	Application entry point for opengl.
 *
 *	author schell
 *	since 19.12.2009
 */
//--------------------------------------
//  Notification Names and Types
//--------------------------------------
class n_name
{
public:
	enum name
    {
		NIL,					// nothing at all
        STARTUP,                // triggers the app startup sequence
        PATTERNS_REGISTERED,	// alerts the app that proxies and mediators have been registered
		CREATE,					// create something
        DISPLAY,				// display something
        QUIT                    // quit
	};
	static map<int, string> toString;
	static void init()
	{
		n_name::toString[NIL]					= "null";
		n_name::toString[STARTUP] 				= "startup";
        n_name::toString[PATTERNS_REGISTERED] 	= "patterns registered";
        n_name::toString[CREATE] 				= "create";			    
        n_name::toString[DISPLAY] 				= "display";			    
		n_name::toString[QUIT] 					= "quit";                       
	}	
};
map<int, string> n_name::toString;
class n_type
{
public:
    enum type
    {
		NIL,		// nothing
		GL_WINDOW,	// an opengl window
		PROMPT		// some prompt
	};
	static map<int, string> toString;
	static void init()
	{
		n_type::toString[NIL] = "null";
		n_type::toString[THREAD] = "thread";
		n_type::toString[PROMPT] = "prompt";
	}
};
map<int, string> n_type::toString;
//--------------------------------------
//  Mediators
//--------------------------------------
class MouseInputMediator : public Mediator
{
	static const NAME;
	
	MouseInputMediator(string mediatorName) : Mediator(mediatorName){}
	void onRegister()
	{
		cout << "MouseInputMediator::onRegister()\n";
	}
	void onRemove()
	{
		cout << "MouseInputMediator::onRemove()\n";
	}
	// list the notification interests
	vector<int> listNotificationInterests()
	{
		vector<int> interests;
		
		interests.push_back()
	}
};
int width = 640;
int height = 480;
int timer = 0;
//--------------------------------------
//  OpenGL state functions
//--------------------------------------

void display(void)
{	
	// clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// draw!
	for (int xx = 0; xx < width; xx++)
		for (int yy = 0; yy < height; yy++)                
	    {
			unsigned int rgb = (xx + timer | yy + timer) * timer;

			unsigned int r = rgb >> 16;
			unsigned int g = (rgb >> 8) & 0xFF;
			unsigned int b = rgb & 0xFF;
			
			glBegin(GL_POINTS);
			glColor3ub(r, g, b);
			glVertex2i(xx, yy);
			glEnd();
			//cout << "\n" << rgb << "\n";
		}
	timer+=10;
	// move rear buffer to visible
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
    glutPostRedisplay();
}

//--------------------------------------
//  MAIN
//--------------------------------------

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("opengl");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    glutMainLoop();

    return EXIT_SUCCESS;
}