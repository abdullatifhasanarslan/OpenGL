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


class factorial : public Function{
	public:
		factorial(Variable<int>* left, Variable<int>* i){
			this->left = left;
			this->i = i;
		}	
		void display(int x, int y){
		
		}
		void implement(){
			//int factorial(int i){
			NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
			Variable<int>* i = new Variable<int>("i",this->i->value);
			NameSpace::active_stack->add_Variable( i );
			Variable<int>* result = new Variable<int>("result",1);
			NameSpace::active_stack->add_Variable( result );
			PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
			int depth=0;
			//while(i>1)
			Variable<int>* deneme = new Variable<int>("",1);
			PipeLine::active_pipeline->add_Command( new Command(depth, WHILE, "while(i>1)", new greaterthan< Variable<int>, Variable<int> >(i, deneme) ) );
			//{
			PipeLine::active_pipeline->add_Command( new Command(++depth, OPEN_SCOPE) );
			//result *= i;
			PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "result*=i", new multiply_and_assign< Variable<int> ,Variable<int>>(result, i) ) );
			//i--;
			PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "i--", new post_decrement(i) ) );
			//}
			PipeLine::active_pipeline->add_Command( new Command(depth--, CLOSE_LOOP_SCOPE) );
			//return result
			PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "return result", new returner<Variable<int>>(this->left, result) ) );
			//-------------------
			//this->name=this->left_name + " = " + std::to_string(this->return_value);
			PipeLine::active_pipeline->commands[0]->is_current=true;
			this->display(this->x,this->y);
			glutPostRedisplay();
			glFlush();
		}
		int result;
		Variable<int>* i;
		
	private:
		Variable<int>* left;
};





void init(void){
	glClearColor(0.15294f, 0.15686f, 0.13333, 0);
	glShadeModel(GL_FLAT);
	glEnable(GL_POLYGON_STIPPLE);

	NameSpace::active_stack = new NameSpace();
	int depth=0;
	PipeLine::active_pipeline = new PipeLine();
	heap = new NameSpace();
	global = new NameSpace(); 
	Variable<int>* k = new Variable<int>("k");
	global->add_Variable( k );
	// Variable<int>* sil = new Variable<int>("sil",1);
	// global->add_Variable( sil );
	//int i;
	Variable<int>* _i = new Variable<int>("i");
	NameSpace::active_stack->add_Variable( _i );
	//int temp;
	Variable<int>* _temp = new Variable<int>("temp");
	NameSpace::active_stack->add_Variable( _temp );
	//#define SIZE 10
	#define SIZE 10
	//int array[SIZE];
	int array[SIZE]={0};	
	Array<int>* _array = new Array<int>("array", array, SIZE);
	NameSpace::active_stack->add_Variable( _array );
	//i=0;
	Variable<int>* deneme = new Variable<int>("",0);
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "i=0", new assignment< Variable<int> >(_i, deneme) ) );
	//while(i<SIZE)
	Variable<int>* deneme2 = new Variable<int>("",SIZE);
	PipeLine::active_pipeline->add_Command( new Command(depth, WHILE, "while(i<size)", new lessthan< Variable<int>, Variable<int> >(_i, deneme2) ) );
	//{
	PipeLine::active_pipeline->add_Command( new Command(++depth, OPEN_SCOPE,"{") );
	//temp = factorial(i);
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "temp=factorial(i)", new factorial(_temp, _i) ) );
	//if(i%2)
	Variable<int>* deneme3 = new Variable<int>("",2);
	PipeLine::active_pipeline->add_Command( new Command(depth, IF, "if(i%2)", new modulo(_i, deneme3) ) );
	//	{
	PipeLine::active_pipeline->add_Command( new Command(++depth, OPEN_SCOPE,"{") );
	//	i++;
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "i++", new post_increment(_i) ) );
	//	}
	PipeLine::active_pipeline->add_Command( new Command(depth--, CLOSE_SCOPE,"}") );
	//else if(i>5)
	Variable<int>* deneme4 = new Variable<int>("",5);
	PipeLine::active_pipeline->add_Command( new Command(depth, ELSE_IF, "else if(i>5)", new greaterthan<Variable<int>,Variable<int>>(_i, deneme4) ) );
	//{
	PipeLine::active_pipeline->add_Command( new Command(++depth, OPEN_SCOPE,"{") );
	//i=0;
	Variable<int>* deneme5 = new Variable<int>("",5);
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "i=0", new assignment< Variable<int> >(_i, deneme5) ) );
	//}
	PipeLine::active_pipeline->add_Command( new Command(depth--, CLOSE_SCOPE,"}") );
	//else
	PipeLine::active_pipeline->add_Command( new Command(depth, ELSE,"else"));
	//{
	PipeLine::active_pipeline->add_Command( new Command(++depth, OPEN_SCOPE,"{") );
	//i*=2;
	Variable<int>* deneme6 = new Variable<int>("",2);
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "i*=2", new multiply_and_assign< Variable<int> ,Variable<int>>(_i, deneme6) ) );
	//}
	PipeLine::active_pipeline->add_Command( new Command(depth--, CLOSE_SCOPE, "}") );
	//array[i] = temp;
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "array[i]=temp", new array_assignment(_array, _i, _temp) ) );
	//i++;
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, "i++", new post_increment(_i) ) );
	//}
	PipeLine::active_pipeline->add_Command( new Command(depth--, CLOSE_LOOP_SCOPE, "}") );
	//return EXIT_SUCCESS
	
}


















#endif