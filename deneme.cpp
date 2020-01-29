#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "events.h"
#include "models.h"
#include "Variables.h"
#include "Functions.h"
#include "utility.h"

using namespace std;

vector<entity*> entity::all_variables;
//DRAW--------------------------
void init(void);
void display(void);
void spinDisplay();


//VARIABLES---------------------
int WindowX = 640;
int WindowY = 360;
int Width = 1000;
int Height = 360;
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
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseDragged);
	glutIdleFunc(IDLE);
	
	glutMainLoop();
	return 0;
}

void init(void){
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glShadeModel(GL_FLAT);

	new Variable<char>("character",'a');
	new Variable<double>("double_number",31.4561234);
	new Variable<float>("float_number",16.28);
	new Variable<int>("integer_number",30);
	new Variable<bool>("boolean",true);
	new Variable<bool>("newbool",false);
	entity* current;
	int size = entity::all_variables.size();
	for(int i=0;i<size;i++){
		current=entity::all_variables[i];
		current->setPose(i*25,i*50);
		//std::cout << (*current) << endl;
	}
}

void display(void){
	//clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		//Some settings
		glColor3f(0.7, 0.7, 0.0);
		glLineWidth(20.0);
		entity* current;
		int size = entity::all_variables.size();
		for(int i=0;i<size;i++){
			current=entity::all_variables[i];
			current->display();
		}
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
		glEnable(GL_LINE_STIPPLE);
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
