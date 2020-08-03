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
	this->active=true;
}

void Command::display(int x, int y){
	glPushMatrix();
		this->active ? glColor3f(0.7,0.7,0.0) : glColor3f(0.7,0.0,0.0);
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
			case ELSE_IF:
			case WHILE:
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
			case CLOSE_LOOP_SCOPE:
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
	this->active=true;
}

void Command::implement(){
	if(this->func!=NULL){
		cout << this->func->name << endl;
		this->func->implement();
	}
	if(this->type != WHILE && this->type != IF && this->type != ELSE_IF){
		this->active=false;
	}else{
		this->active = this->func->return_value;
		cout << "returned" << this->active << endl;
	}
	
}

int Command::get_type(){
	return this->type;
}

int Command::get_level(){
	return this->level;
}

bool Command::is_active(){
	return this->active;
}

void Command::disable(){
	this->active=false;
}

void Command::activate(){
	this->active=true;
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

void PipeLine::come_back(int level){
	while(this->commands[this->current]->get_type() != WHILE || this->commands[this->current]->get_level() != level-1){
		//I could also check their type and reactivate if they are deactivated
		//This is a nice thing to remember since I could also show commented commands
		//Igmpring some details was waaaay more easy,
		this->commands[this->current--]->activate();
	}
	this->commands[this->current]->activate();
	//step will increase 1
	this->current--;
}


void PipeLine::skip(int level){
	//skip current command and open_bracket
	//this->current+=2;
	++this->current;
	while(this->commands[this->current]->get_type()!=CLOSE_SCOPE && this->commands[this->current]->get_type()!=CLOSE_LOOP_SCOPE){
		this->commands[this->current]->disable();
		++this->current;
	}
	this->commands[this->current]->disable();	
	//step will skip close bracket
}

void PipeLine::disable_else(int level){
	int i=this->current;
	while( this->commands[i]->get_type() != ELSE || this->commands[i]->get_level() != level ){
		this->commands[i]->disable();
		i++;
	}
	this->commands[i]->disable();
}

void PipeLine::step(){
	cout << "önce: " << this->commands[this->current]->is_active() << endl;
	this->commands[this->current]->implement(); //if it is conditional <active> should be determined inside
	cout << "sonra: " << this->commands[this->current]->is_active() << endl;
	switch( this->commands[this->current]->get_type() ){
		case IF:
		case ELSE_IF:
			if( this->commands[this->current]->is_active() ){
				this->disable_else(this->commands[this->current]->get_level());
			} else{
				this->skip(this->commands[this->current]->get_level());
			}
			break;
		case WHILE:
		case ELSE:
			if( ! this->commands[this->current]->is_active() ){
				cout << ":" << this->current << endl;
				this->skip(this->commands[this->current]->get_level());
				cout << ":" << this->current << endl;
			}
			break;
		case CLOSE_LOOP_SCOPE:
			this->come_back(this->commands[this->current]->get_level());
		default:
			break;
	}
	if(++this->current==this->commands.size()){
		cout << "heeymaan" << endl;
		if(this->parent!=NULL){
			PipeLine::active_pipeline=this->parent;
			NameSpace::active_stack=NameSpace::active_stack->get_parent();
			//destroy this
		} else {
			cout<<"Program should be terminated but restarts instead"<<endl;
			this->current=0;
		}
		// } else{
		// 	cout<<"Execution finished"<<endl;
		// 	exit(0);
		// }
	}
}