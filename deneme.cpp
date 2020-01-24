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

//DRAW--------------------------
void init(void);
void display(void);
void spinDisplay();


//VARIABLES---------------------
int WindowX = 640;
int WindowY = 360;
int Width = 640;
int Height = 360;
const char* WindowName = "Spinner";
extern GLubyte fly[], halftone[];

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
}

void display(void){
	//clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	Char character = Char("character",'a');
	Double double_number = Double("double_number",3.14561234);
	Float float_number = Float("float_number",1.628);
	Int integer_number = Int("integer_number",3);
	std::cout << 1 << endl;
	std::cout << character << endl;
	std::cout << double_number << endl;
	std::cout << float_number << endl;
	std::cout << integer_number << endl;
	/*
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
