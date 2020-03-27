#include "all_functions.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

extern int Width;
extern int Height;

//---------------------------------------------------------

user_defined1::user_defined1(){

}

void user_defined1::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.1, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.1);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined1::implement(){
}

//---------------------------------------------------------

user_defined2::user_defined2(){
}

void user_defined2::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.2, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.2);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined2::implement(){
	
}

//---------------------------------------------------------

user_defined3::user_defined3(){
}

void user_defined3::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.3, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.3);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined3::implement(){
	
}

//---------------------------------------------------------

user_defined4::user_defined4(){
}

void user_defined4::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.4, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.4);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined4::implement(){
	
}

//---------------------------------------------------------

user_defined5::user_defined5(){
}

void user_defined5::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.5, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.5);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined5::implement(){
	
}

//---------------------------------------------------------

user_defined6::user_defined6(){
}

void user_defined6::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.6, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.6);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined6::implement(){
	
}

//---------------------------------------------------------

user_defined7::user_defined7(){
}

void user_defined7::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.7, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.7);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined7::implement(){
	
}

//---------------------------------------------------------

user_defined8::user_defined8(){
}

void user_defined8::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.8, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.8);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined8::implement(){
	
}

//---------------------------------------------------------

user_defined9::user_defined9(){
}

void user_defined9::display(int x, int y){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.9, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, 0.0, 0.9);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined9::implement(){
	
}

//---------------------------------------------------------

user_defined10::user_defined10(int r, int g, int b){
	this->r=r;
	this->g=g;
	this->b=b;
}

void user_defined10::display(int x, int y){
	this->x=x;
	this->y=y;
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(r/10.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-10);
			glVertex2d(x,Height-y-20);
			glVertex2d(x+200,Height-y-20);
			glVertex2d(x+200,Height-y-10);
		glEnd();
		glColor3f(0.0, g/10.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-20);
			glVertex2d(x,Height-y-30);
			glVertex2d(x+200,Height-y-30);
			glVertex2d(x+200,Height-y-20);
		glEnd();
		glColor3f(0.0, 0.0, b/10.0);
		glBegin(GL_POLYGON);
			glVertex2d(x,Height-y-30);
			glVertex2d(x,Height-y-40);
			glVertex2d(x+200,Height-y-40);
			glVertex2d(x+200,Height-y-30);
		glEnd();
	glPopMatrix();
}

void user_defined10::implement(){
	int temp=this->r;
	this->r=this->g;
	this->g=this->b;
	this->b=temp;
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(this->r/10.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(this->x,Height-this->y-10);
			glVertex2d(this->x,Height-this->y-20);
			glVertex2d(this->x+200,Height-this->y-20);
			glVertex2d(this->x+200,Height-this->y-10);
		glEnd();
		glColor3f(0.0, this->g/10.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(this->x,Height-this->y-20);
			glVertex2d(this->x,Height-this->y-30);
			glVertex2d(this->x+200,Height-this->y-30);
			glVertex2d(this->x+200,Height-this->y-20);
		glEnd();
		glColor3f(0.0, 0.0, this->b/10.0);
		glBegin(GL_POLYGON);
			glVertex2d(this->x,Height-this->y-30);
			glVertex2d(this->x,Height-this->y-40);
			glVertex2d(this->x+200,Height-this->y-40);
			glVertex2d(this->x+200,Height-this->y-30);
		glEnd();
	glPopMatrix();
	glFlush();
}