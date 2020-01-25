#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "events.h"
#include "Variables.h"

using namespace std;

void reshape(int w, int h);
void keyPressed(unsigned char key, int x, int y);
void mousePressed(int button, int state, int x, int y);
void mouseDragged(int x, int y);
void IDLE();
extern void Spin();

extern int Width;
extern int Height;

extern Variable<char> character;
extern Variable<double> double_number;
extern Variable<float> float_number;
extern Variable<int> integer_number;
extern Variable<bool> boolean;

void reshape(int w, int h){
	Width=w;
	Height=h;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void keyPressed(unsigned char key, int x, int y){
	switch(key){
		case 27:
			cout << "Terminating---------" << endl;
			exit (0);
			break;
		//default:
			//cout << key << "," << x << "," << y << endl;
	}
}
void mousePressed(int button, int state, int x, int y){
	/*switch(button){
		default:
			//cout << button << "," << state << "," << x << "," << y << endl;
	}*/
}
void mouseDragged(int x, int y){
	//Gives current coordinates
	cout << x << "," << Height-y << endl;
	if(character.checkCollision(x,Height-y)){
		character.setPose(x-10,Height-y-10);
	}
	if(double_number.checkCollision(x,Height-y)){
		double_number.setPose(x-10,Height-y-10);
	}
	if(float_number.checkCollision(x,Height-y)){
		float_number.setPose(x-10,Height-y-10);
	}
	if(integer_number.checkCollision(x,Height-y)){
		integer_number.setPose(x-10,Height-y-10);
	}
	if(boolean.checkCollision(x,Height-y)){
		boolean.setPose(x-10,Height-y-10);
	}
	cout << endl << endl;
	glutPostRedisplay();
}
void IDLE(){
	//Works if no other event exist
	//cout << "Allah" << endl;
}

