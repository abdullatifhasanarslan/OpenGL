#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "events.h"

using namespace std;

void reshape(int w, int h);
void keyPressed(unsigned char key, int x, int y);
void mousePressed(int button, int state, int x, int y);
void mouseDragged(int x, int y);
void IDLE();
extern void Spin();


extern int Width;
extern int Height;

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
	//cout << x << "," << y << endl;
}
void IDLE(){
	//Works if no other event exist
	//cout << "Allah" << endl;
}

