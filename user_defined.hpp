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
class absolute_difference : public Function {
	public:
		Variable<int>* left;
		Variable<int>* a;
		Variable<int>* b;
		Variable<int>* result;
		absolute_difference(Variable<int>* left,Variable<int>* a,Variable<int>* b){
			this->left=left;
			this->a=a;
			this->b=b;
		}
		void display(int x, int y){
		}
		void implement(){
			NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
			Variable<int>* a= new Variable<int>("a",this->a->value);
			NameSpace::active_stack->add_Variable(a);
			Variable<int>* b= new Variable<int>("b",this->b->value);
			NameSpace::active_stack->add_Variable(b);
			Variable<int>* result= new Variable<int>("result");
			NameSpace::active_stack->add_Variable(result);
			PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
			PipeLine::active_pipeline->add_Command( new Command(0,OPEN_SCOPE,"{"));
			PipeLine::active_pipeline->add_Command( new Command(0,IF,"if ( a > b )",new greaterthan<Variable<int>>(a,b)));
			PipeLine::active_pipeline->add_Command( new Command(1,OPEN_SCOPE,"{"));
			PipeLine::active_pipeline->add_Command( new Command(1,NORMAL,"result = a - b ;",new subtraction<Variable<int>>(result,a,b)));
			PipeLine::active_pipeline->add_Command( new Command(1,CLOSE_SCOPE,"}"));
			PipeLine::active_pipeline->add_Command( new Command(0,ELSE,"else"));
			PipeLine::active_pipeline->add_Command( new Command(1,OPEN_SCOPE,"{"));
			PipeLine::active_pipeline->add_Command( new Command(1,NORMAL,"result = b - a ;",new subtraction<Variable<int>>(result,b,a)));
			PipeLine::active_pipeline->add_Command( new Command(1,CLOSE_SCOPE,"}"));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"return result ;",new returner<Variable<int>>(this->left,result)));
			PipeLine::active_pipeline->add_Command( new Command(0,CLOSE_SCOPE,"}"));
		}
};
class array_test : public Function {
	public:
		Variable<int>* left;
		Array<char>* array_[5];
		array_test(Variable<int>* left){
			this->left=left;
		}
		void display(int x, int y){
		}
		void implement(){
			NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
	char array_[5];
	Array<char>* array=new Array<char>("array",array_,5);
			NameSpace::active_stack->add_Variable(array);
			PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
			PipeLine::active_pipeline->add_Command( new Command(0,OPEN_SCOPE,"{"));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"array [ 0 ] = 'a' ;",new array_assignment<char>(array,new Variable<int>("",0),new Variable<char>("",'a'))));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"array [ 1 ] = 'b' ;",new array_assignment<char>(array,new Variable<int>("",1),new Variable<char>("",'b'))));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"array [ 2 ] = 'c' ;",new array_assignment<char>(array,new Variable<int>("",2),new Variable<char>("",'c'))));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"array [ 3 ] = 'd' ;",new array_assignment<char>(array,new Variable<int>("",3),new Variable<char>("",'d'))));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"array [ 4 ] = 'e' ;",new array_assignment<char>(array,new Variable<int>("",4),new Variable<char>("",'e'))));
			PipeLine::active_pipeline->add_Command( new Command(0,CLOSE_SCOPE,"}"));
		}
};
class average : public Function {
	public:
		Variable<int>* left;
		Variable<int>* a;
		Variable<int>* b;
		Variable<int>* c;
		Variable<int>* result;
		average(Variable<int>* left,Variable<int>* a,Variable<int>* b,Variable<int>* c){
			this->left=left;
			this->a=a;
			this->b=b;
			this->c=c;
		}
		void display(int x, int y){
		}
		void implement(){
			NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
			Variable<int>* a= new Variable<int>("a",this->a->value);
			NameSpace::active_stack->add_Variable(a);
			Variable<int>* b= new Variable<int>("b",this->b->value);
			NameSpace::active_stack->add_Variable(b);
			Variable<int>* c= new Variable<int>("c",this->c->value);
			NameSpace::active_stack->add_Variable(c);
			Variable<int>* result= new Variable<int>("result");
			NameSpace::active_stack->add_Variable(result);
			PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
			PipeLine::active_pipeline->add_Command( new Command(0,OPEN_SCOPE,"{"));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"result = a + b ;",new addition<Variable<int>>(result,a,b)));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"result = result + c ;",new addition<Variable<int>>(result,result,c)));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"result = result / 3 ;",new division<Variable<int>>(result,result,new Variable<int>("",3))));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"return result ;",new returner<Variable<int>>(this->left,result)));
			PipeLine::active_pipeline->add_Command( new Command(0,CLOSE_SCOPE,"}"));
		}
};
class factorial : public Function {
	public:
		Variable<int>* left;
		Variable<int>* i;
		Variable<int>* result;
		factorial(Variable<int>* left,Variable<int>* i){
			this->left=left;
			this->i=i;
		}
		void display(int x, int y){
		}
		void implement(){
			NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
			Variable<int>* i= new Variable<int>("i",this->i->value);
			NameSpace::active_stack->add_Variable(i);
			Variable<int>* result= new Variable<int>("result",1);
			NameSpace::active_stack->add_Variable(result);
			PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
			PipeLine::active_pipeline->add_Command( new Command(0,OPEN_SCOPE,"{"));
			PipeLine::active_pipeline->add_Command( new Command(0,WHILE,"while ( i > 1 )",new greaterthan<Variable<int>>(i,new Variable<int>("",1))));
			PipeLine::active_pipeline->add_Command( new Command(1,OPEN_SCOPE,"{"));
			PipeLine::active_pipeline->add_Command( new Command(1,NORMAL,"result *= i ;",new multiply_and_assign<Variable<int>>(result,i)));
			PipeLine::active_pipeline->add_Command( new Command(1,NORMAL,"i -- ;",new post_decrement(i)));
			PipeLine::active_pipeline->add_Command( new Command(1,CLOSE_LOOP_SCOPE,"}"));
			PipeLine::active_pipeline->add_Command( new Command(0,NORMAL,"return result ;",new returner<Variable<int>>(this->left,result)));
			PipeLine::active_pipeline->add_Command( new Command(0,CLOSE_SCOPE,"}"));
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
	int array_[3];
	Array<int>* array=new Array<int>("array",array_,3);
	NameSpace::active_stack->add_Variable(array);
	Variable<int>* temp=new Variable<int>("temp");
	NameSpace::active_stack->add_Variable(temp);
	PipeLine::active_pipeline->add_Command(new Command(0,OPEN_SCOPE,"{"));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"temp = factorial ( 10 ) ;",new factorial(temp,new Variable<int>("",10))));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"array [ 0 ] = temp ;",new array_assignment<int>(array,new Variable<int>("",0),temp)));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"temp = absolute_difference ( 10 , 20 ) ;",new absolute_difference(temp,new Variable<int>("",10),new Variable<int>("",20))));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"array [ 1 ] = temp ;",new array_assignment<int>(array,new Variable<int>("",1),temp)));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"temp = average ( 10 , 20 , 30 ) ;",new average(temp,new Variable<int>("",10),new Variable<int>("",20),new Variable<int>("",30))));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"array [ 2 ] = temp ;",new array_assignment<int>(array,new Variable<int>("",2),temp)));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"array_test ( ) ;",new array_test(NULL)));
	PipeLine::active_pipeline->add_Command(new Command(0,NORMAL,"return 0 ;",new returner<Variable<int>>(NULL,new Variable<int>("",0))));
	PipeLine::active_pipeline->add_Command(new Command(0,CLOSE_SCOPE,"}"));
}
#endif
