#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "events.h"
#include "Variables.h"
#include "Functions.h"

using namespace std;

extern void Spin();

extern int Width;
extern int Height;
extern NameSpace* active_stack;
extern NameSpace* heap;
extern NameSpace* global; 

int postX, postY;
int viewX=0;//left
int viewY=0;//bottom
double scale=1.0;
int current=0;

void reshape(int w, int h){
	Width=w;
	Height=h;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(viewX, (GLdouble) (viewX+Width/scale), viewY, (GLdouble) (viewY+Height/scale));
}

void keyPressed(unsigned char key, int x, int y){
	switch(key){
		case 27:
			cout << "Terminating---------" << endl;
			exit (0);
			break;
		case 13:
			int size=PipeLine::active_pipeline->commands.size();
			if(++current==size){
				current=0;
			}
			PipeLine::active_pipeline->commands[current]->implement();
			break;
		// default:
		// 	cout << key << "," << x << "," << y << endl;
	}
}

void specialPressed(int key, int x, int y){
	switch(key){
		case 100:
			// cout << "LEFT" << endl;
			viewX-=100;
			break;
		case 101:
			// cout << "UP" << endl;
			viewY+=100;
			break;
		case 102:
			// cout << "RIGHT" << endl;
			viewX+=100;
			break;
		case 103:
			// cout << "DOWN" << endl;
			viewY-=100;
			break;
		default:
			cout << key << "," << x << "," << y << endl;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(viewX, (GLdouble) (viewX+Width/scale), viewY, (GLdouble) (viewY+Height/scale));
	glutPostRedisplay();
}

void mousePressed(int button, int state, int x, int y){
	postX=viewX+(x/scale);
	postY=(y/scale)-((Height/scale)-Height)-viewY;
	switch(button){
		case 3:
			if(state==0){
				scale+=0.1;
			}
			break;
		case 4:
			if(state==0){
				scale-=0.1;
			}
			break;
		default:
			cout << button << "," << state << "," << x << "," << y << endl;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(viewX, (GLdouble) (viewX+Width/scale), viewY, (GLdouble) (viewY+Height/scale));
	glutPostRedisplay();
}
void mouseDragged(int x, int y){
	//Gives current coordinates
	cout << x << "," << y << endl;
	int X=viewX+(x/scale);
	int Y=(y/scale)-((Height/scale)-Height)-viewY;
	cout << X << "," << Y << endl; 
	entity* current;
	int size = active_stack->ordered.size();
	for(int i=0;i<size;i++){
		current=active_stack->ordered[i];
		if(current->checkCollision(X,Y)){
			cout << "COLLISION" << endl;
			// current->setPose(current->x+(X-postX),current->y+(Y-postY));
		}
	}
	cout << endl << endl;
	postX=viewX+(x/scale);
	postY=(y/scale)-((Height/scale)-Height)-viewY;
	glutPostRedisplay();
}
void IDLE(){
	//Works if no other event exist
	//cout << "Allah" << endl;
}

