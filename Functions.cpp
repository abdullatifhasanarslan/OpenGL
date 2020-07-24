#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "Functions.h"
#include "utility.h"

using namespace std;

extern int Width;
extern int Height;
extern void RenderString(int x, int y, const std::string &string, void* font=GLUT_BITMAP_TIMES_ROMAN_24);


//---------------------------------------------------------

Function::Function(){

}

Function::~Function(){

}

//---------------------------------------------------------

Command::Command(int level, int type, Function* func){
	this->level=level;
	this->type=type;
	this->func=func;
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
			this->func->display(x,y);
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
	this->current=0;
	this->parent=NULL;
}
PipeLine::PipeLine(PipeLine* parent){
	this->current=0;
	this->parent=parent;
	// PipeLine::active_pipeline=this;
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

void PipeLine::step(){
	this->commands[current]->implement();
	if(++this->current==this->commands.size()){
		if(this->parent!=NULL){
			PipeLine::active_pipeline=this->parent;
			NameSpace::active_stack=NameSpace::active_stack->get_parent();
			//destroy this
		} else {
			cout<<"Program should be terminated but restarts instead"<<endl;
			this->current=0;
		}
	}
}