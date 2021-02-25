#ifdef _WIN32
#include <windows.h>
#endif
#ifdef _WIN64
#include <windows.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include "events.h"
#include "models.h"
#include "Variables.h"
#include "Functions.h"
#include "user_defined.hpp"
#include "utility.h"
#include "all_functions.h"
using namespace std;

//DRAW--------------------------
void init(void);
void display(void);
void spinDisplay();
void drawFuncSquare();
void drawStackSquare();

// void RenderString(GLdouble x, GLdouble y, const std::string &string){
// 	glColor3d(1.0, 0.0, 0.0);
// 	glRasterPos2f(x,y);
// 	for(int n=0; n<string.size(); n++){
// 		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[s]);
// 	}
// }

string int_to_string(int a){
	string str = std::to_string(a);
	return str;
}


void RenderString(int x, int y, const std::string &string, void* font=GLUT_BITMAP_TIMES_ROMAN_24){
	// glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(x,y);
	for(uint n=0; n<string.size(); n++){
		glutBitmapCharacter(font, string[n]);
	}
}


//VARIABLES---------------------
int WindowX = 0;
int WindowY = 0;
int Width = 1920;
int Height = 1080;
const char* WindowName = "deneme";

/*
 *	Request double buffer display mode.
 *	Register mouse input callback functions
 */
int main(int argc, char** argv){
	//WINDOW--------------------
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Width,Height);
	glutInitWindowPosition(WindowX,WindowY);
	glutCreateWindow(WindowName);
	glutFullScreen();

	//DISPLAY-------------------
	init();
	glutDisplayFunc(display);

	//CONTROL-------------------
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialPressed);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseDragged);
	glutIdleFunc(IDLE);
	
	glutMainLoop();
	return 0;
}


void display(void){
	//clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		//Some settings
		glColor3f( 0.65098f, 0.88627f, 0.18039f );
		glLineWidth(10.0);
		
		//drawing rectangles
		drawFuncSquare();
		drawStackSquare();
		//drawing stack
		int last_pose=225;
		int size = NameSpace::active_stack->ordered.size();
		for(int i=0; i<size; i++){
			NameSpace::active_stack->ordered[i]->display(375,last_pose);
			last_pose+=NameSpace::active_stack->ordered[i]->getheight()+30;
		}
		//drawing heap
		last_pose=225;
		size = heap->ordered.size();
		for(int i=0; i<size; i++){
			heap->ordered[i]->display(75,last_pose);
			last_pose+=heap->ordered[i]->getheight()+30;
		}
		//drawing globals
		last_pose=375;
		size = global->ordered.size();
		for(int i=0; i<size; i++){
			global->ordered[i]->display(last_pose,50);
			last_pose+=global->ordered[i]->getwidth()+30;
		}

		PipeLine::active_pipeline->display();
		// string test("heeeeyoooo");
		// RenderString(500,500,test);
	glPopMatrix();
	glFlush();
}

/*
				 	 |50
				 	 |50-200-25
				 	 |50
			-----------------------------			
			| 	 	 |50				|
			|	------------			|
			|	|	 |25   |			|
-75-200-50- |-25|-25-200-25|-25-25-200	|50
			|	|		   |			|
			|	|		   |			|
			|	------------			|
			|						  	|
			-----------------------------
*/



void drawStackSquare(){
	glPushMatrix();
		//Some settings
		glColor3f( 0.65098f, 0.88627f, 0.18039f );
		glLineWidth(1.0);
		// glBegin(GL_LINE_LOOP);
		glBegin(GL_LINES);
			glVertex2d(350,Height-950);
			glVertex2d(350,Height-200);
			
			glVertex2d(350,Height-200);
			glVertex2d(600,Height-200);
			
			glVertex2d(600,Height-200);
			glVertex2d(600,Height-950);
		glEnd();	
	glPopMatrix();

}

void drawFuncSquare(){
	glPushMatrix();
		//Some settings
		glColor3f( 0.65098f, 0.88627f, 0.18039f );
		glLineWidth(1.0);
		// glBegin(GL_LINE_LOOP);
		glBegin(GL_LINES);
			glVertex2d(325,Height-1000);
			glVertex2d(325,Height-150);
			
			glVertex2d(325,Height-150);
			glVertex2d(1875,Height-150);
			
			glVertex2d(1875,Height-150);
			glVertex2d(1875,Height-1000);
		glEnd();	
	glPopMatrix();
}
