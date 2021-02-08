#ifndef USER_DEFINED_HPP
#define USER_DEFINED_HPP
#include "Variables.h"
#include "Functions.h"
#include "all_functions.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
NameSpace* heap;
NameSpace* global; 
PipeLine* PipeLine::active_pipeline;
NameSpace* NameSpace::active_stack;
Variable<int>* k;
class factorial : public Function {
	public:
		Variable<int>* left;
		Variable<int>* i;
		Variable<int>* result;
		factorial(Variable<int>* leftVariable<int>* i){
			this->left=left;
			this->i=i;
		}
		void display(int x, int y){
		}
		void implement(){
			NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
			Variable<int>* i= new Variable<int>("i",this->i->value);
			Variable<int>* result= new Variable<int>("result",1);
			int depth=0;
			PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
			//while(i>1)
			PipeLine::active_pipeline->add_Command( new Command(0,WHILE,"while(i>1)",new greaterthan<Variable<int>,Variable<int>>(i,new Variable<int>("",1))));
			//{
			PipeLine::active_pipeline->add_Command( new Command(1,OPEN_SCOPE,"{"));
			//result*=i
			PipeLine::active_pipeline->add_Command( new Command(1,NORMAL,"result*=i",new multiply_and_assign<Variable<int>,Variable<int>>(result,i)));
			//i
			PipeLine::active_pipeline->add_Command( new Command(1,NORMAL,"i",new post_decrement(i)));
			//}
			PipeLine::active_pipeline->add_Command( new Command(1,CLOSE_LOOP_SCOPE,"}"));
			//return result
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"return result",new returner<Variable<int>>(this->left,result)));
		}
};
void init(void){
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_POLYGON_STIPPLE);
	heap = new NameSpace();
	global = new NameSpace();
k=new Variable<int>("k");
global->add_Variable(k);
	NameSpace::active_stack = new NameSpace();
	PipeLine::active_pipeline = new PipeLine();
	int depth=0;
	//int array[10];
	int array["10"];
	Array<int>* array=new Array<int>("array",array,10);
	NameSpace::active_stack->add_Variable(array);
	//int i=0;
	Variable<int>* i=new Variable<int>("i",0);
	NameSpace::active_stack->add_Variable(i);
	//int temp=0;
	Variable<int>* temp=new Variable<int>("temp",0);
	NameSpace::active_stack->add_Variable(temp);
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"i=0;",new assignment<Variable<int>>(i,new Variable<int>("",0))));
	PipeLine::active_pipeline->add_Command(new Command(0,WHILE,"while(i<5)",new lessthan<Variable<int>,Variable<int>>(i,new Variable<int>("",5))));
	PipeLine::active_pipeline->add_Command(new Command(1,OPEN_SCOPE,"{"));
	PipeLine::active_pipeline->add_Command(new Command(1,NORMAL,"temp=factorial(i)",new factorial(temp,i)));
	PipeLine::active_pipeline->add_Command(new Command(1,IF,"if(i%2)",new modulo(i,new Variable<int>("",2))));
	PipeLine::active_pipeline->add_Command(new Command(2,OPEN_SCOPE,"{"));
	PipeLine::active_pipeline->add_Command(new Command(2,NORMAL,"i++;",new post_increment(i)));
	PipeLine::active_pipeline->add_Command(new Command(2,CLOSE_SCOPE,"}"));
	PipeLine::active_pipeline->add_Command(new Command(1,ELSE_IF,"else if(i>5)",new greater_than(i,new Variable<int>("",5))));
	PipeLine::active_pipeline->add_Command(new Command(2,OPEN_SCOPE,"{"));
	PipeLine::active_pipeline->add_Command(new Command(2,NORMAL,"i=0;",new assignment<Variable<int>>(i,new Variable<int>("",0))));
	PipeLine::active_pipeline->add_Command(new Command(2,CLOSE_SCOPE,"}"));
	PipeLine::active_pipeline->add_Command(new Command(1,ELSE,"else"));
	PipeLine::active_pipeline->add_Command(new Command(2,OPEN_SCOPE,"{"));
	PipeLine::active_pipeline->add_Command(new Command(2,NORMAL,"i*=2;",new multiply_and_assign<Variable<int>,Variable<int>>(i,new Variable<int>("",2))));
	PipeLine::active_pipeline->add_Command(new Command(2,CLOSE_SCOPE,"}"));
	PipeLine::active_pipeline->add_Command(new Command(1,NORMAL,"array[i]=temp;",new array_assignment(array,i,temp)));
	PipeLine::active_pipeline->add_Command(new Command(1,NORMAL,"i++;",new post_increment(i)));
	PipeLine::active_pipeline->add_Command(new Command(1,CLOSE_LOOP_SCOPE,"}"));
}
