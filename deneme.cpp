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
	/*
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		//Some settings
		glTranslatef((GLdouble) Width/2, (GLdouble) Height/2, 0.0);
		glColor3f(0.7, 0.7, 0.0);
		glLineWidth(20.0);

		//Outer Rectangle
		glEnable(GL_LINE_STIPPLE);dd
		glLineStipple(5, 0x5555);
		Line(50-Width/2,Height/2-50,Width/2-50,Height/2-50);
		glLineStipple(10, 0x3333);
		Line(Width/2-50,Height/2-50,Width/2-50,50-Height/2);
		glLineStipple(10, 0xB778);
		Line(Width/2-50,50-Height/2,50-Width/2,50-Height/2);
		glLineStipple(10, 0x1C47);
		Line(50-Width/2,50-Height/2,50-Width/2,Height/2-50);
		glDisable(GL_LINE_STIPPLE);
		
		//Circle around
		int circle_points=100;
		double angle;
		glBegin(GL_LINE_LOOP);
			for(int i=0;i<circle_points;i++){
				angle=2*M_PI*i/circle_points;
				glVertex2d(cos(angle)*Width/2.0,sin(angle)*Height/2.0);
			}
		glEnd();

		//Polygon Stipple fly
		glPolygonMode(GL_FRONT, GL_FILL);
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonStipple(fly);
		glBegin(GL_POLYGON);
			for(int i=0;i<circle_points;i++){
				angle=2*M_PI*i/circle_points;
				glVertex2d(cos(angle)*Width/4.0,sin(angle)*Height/4.0);
			}
		glEnd();

		//Polygon Stipple halftone
		glPolygonStipple(halftone);
		glBegin(GL_POLYGON);
			glVertex2d(Width/2.0-200,Height/2.0-200);
			glVertex2d(Width/2.0-100,Height/2.0-200);
			glVertex2d(Width/2.0-100,Height/2.0-100);
			glVertex2d(Width/2.0-200,Height/2.0-100);
		glEnd();
		glDisable(GL_POLYGON_STIPPLE);

		//Red edge flag
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);
			glEdgeFlag(GL_TRUE);
			glColor3f(1.0,0.0,0.0);
			glVertex2d(-Width/2.0+200,-Height/2.0+200);
			glVertex2d(-Width/2.0+100,-Height/2.0+200);
			glEdgeFlag(GL_FALSE);
			glVertex2d(-Width/2.0+100,-Height/2.0+100);
			glEdgeFlag(GL_TRUE);
			glColor3f(0.0,1.0,0.0);
			glVertex2d(-Width/2.0+200,-Height/2.0+100);
		glEnd();

		//Points
		glPointSize(20.0);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2d(Width/2.0-50, 0.0);
			glVertex2d(0.0, Height/2.0-50);
		glEnd();

		//Vertex arrays
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, colors);
		glVertexPointer(2, GL_INT, 0, vertices);
		
		glBegin(GL_TRIANGLES);
			glArrayElement(0);
			glArrayElement(1);
			glArrayElement(6);

			glArrayElement(1);
			glArrayElement(6);
			glArrayElement(2);

			glArrayElement(6);
			glArrayElement(2);
			glArrayElement(3);

			glArrayElement(3);
			glArrayElement(4);
			glArrayElement(6);

			glArrayElement(4);
			glArrayElement(6);
			glArrayElement(5);

			glArrayElement(6);
			glArrayElement(5);
			glArrayElement(0);
		glEnd();
		//GLint indices[]={0,1,2,3,4,5};
		//glDrawElements(GL_TRIANGLES, 6, GL_INT, indices);	//MUST BE GL_UNSIGNED_*
		//glDrawArrays(GL_POLYGON, 0, 6);



	glPopMatrix();
	glFlush();
	*/
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
