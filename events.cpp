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
int postX, postY;

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
	postX=x;
	postY=y;
	/*switch(button){
		default:
			//cout << button << "," << state << "," << x << "," << y << endl;
	}*/
}
void mouseDragged(int x, int y){
	//Gives current coordinates
	cout << x << "," << Height-y << endl;
	entity* current;
	int size = entity::all_variables.size();
	for(int i=0;i<size;i++){
		current=entity::all_variables[i];
		if(current->checkCollision(x,Height-y)){
			current->setPose(current->x+x-postX,current->y-y+postY);
		}
	}
	cout << endl << endl;
	postX=x;
	postY=y;
	glutPostRedisplay();
}
void IDLE(){
	//Works if no other event exist
	//cout << "Allah" << endl;
}

