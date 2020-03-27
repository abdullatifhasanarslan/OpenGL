#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "Functions.h"
#include "utility.h"
#include <string>

using namespace std;

extern int Width;
extern int Height;

void text(std::string str, int x, int y);


//---------------------------------------------------------

Function::Function(){

}

Function::~Function(){

}

//---------------------------------------------------------

Command::Command(string str, int level, int type, Function* func){
	this->level=level;
	this->type=type;
	this->func=func;
	this->str=str;
}

void Command::display(int x, int y){
	glPushMatrix();
		
		glColor3f(0.7, 0.7, 0.0);
		glEnable(GL_LINE_STIPPLE);
		glLineWidth(1.0);

		for(int i=0;i<this->level;i++){
			//left
			glLineStipple(1, 0xFFFF);
			Line(x,Height-y,x,Height-y-50);
			//middle
			glLineStipple(10, 0x5555);
			Line(x+30,Height-y,x+30,Height-y-50);
			x+=60;
		}

		switch(this->type){
			case NORMAL:
				//left and right
				glLineStipple(1, 0xFFFF);
				Line(x,Height-y,x,Height-y-50);
				Line(x+60,Height-y,x+60,Height-y-50);
				//stopper
				Line(x+30,Height-y-50,x+60,Height-y-50);
				//middle
				glLineStipple(10, 0x5555);
				Line(x+30,Height-y,x+30,Height-y-50);
				break;
			case IF:
				//left and right
				glLineStipple(1, 0xFFFF);
				Line(x,Height-y,x,Height-y-50);
				Line(x+60,Height-y,x+60,Height-y-50);
				//stopper
				Line(x+30,Height-y-50,x+60,Height-y-50);
				//middle
				glLineStipple(10, 0x5555);
				Line(x+30,Height-y,x+30,Height-y-50);
				break;
			case ELSE:
				//left and right
				glLineStipple(1, 0xFFFF);
				Line(x,Height-y,x,Height-y-50);
				Line(x+60,Height-y,x+60,Height-y-50);
				//up
				Line(x+30,Height-y,x+60,Height-y);
				//cross
				Line(x,Height-y,x+30,Height-y-50);
				//bottom
				Line(x,Height-y-50,x+30,Height-y-50);
				Line(x+30,Height-y-50,x+60,Height-y-50);
				break;
			case OPEN_SCOPE:
				glLineStipple(1, 0xFFFF);
				//cross
				Line(x,Height-y,x+60,Height-y-50);
				//bottom
				Line(x,Height-y-50,x+30,Height-y-50);
				break;
			case CLOSE_SCOPE:
				glLineStipple(1, 0xFFFF);
				//cross
				Line(x+60,Height-y,x,Height-y-50);
				break;
			default:
				cout << "undefined type" << endl;
		}

		x+=60;
		if(this->func!=NULL){
			text(this->str,x,y);
			//this->func->display(x,y);
		}
		glDisable(GL_LINE_STIPPLE);
	glPopMatrix();
}

void Command::implement(){
	if(this->func!=NULL){
		this->func->implement();
	}
}

//---------------------------------------------------------

PipeLine::PipeLine(){
	this->parent=NULL;
}

void PipeLine::display(){
	int lastPose=225;

	int size=this->commands.size();
	Command* current;
	for(int i=0;i<size;i++){
		current=this->commands[i];
		current->display(625,lastPose);
		lastPose+=50;
	}
}

void PipeLine::add_Command(Command* command){
	this->commands.push_back(command);
}
