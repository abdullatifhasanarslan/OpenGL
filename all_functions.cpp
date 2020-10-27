#include "all_functions.h"
#include "Variables.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

extern int Width;
extern int Height;
extern void RenderString(int x, int y, const std::string &string, void* font=GLUT_BITMAP_TIMES_ROMAN_24);

//---------------------------------------------------------

template <class Type>
assignment< Type >::assignment(std::string left_name, std::string right_name, Type* left, Type* right){
	this->name = left_name + " = " + right_name + ";";
	this->left_name = left_name;
	this->right_name = right_name;
	this->left = left;
	this->right = right;
}

template <class Type>
void assignment<Type>::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}
template <class Type>
void assignment<Type>::implement(){
	this->left->value = this->right->value;
	//this->name=this->left_name + " = " + std::to_string(this->right->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class assignment<Variable<int> >;
//---------------------------------------------------------


array_assignment::array_assignment(std::string array_name, std::string right_name, Array<int>* array, Variable<int>* index, Variable<int>* right){
	this->name = array_name + " = " + right_name + ";";
	this->array_name = array_name;
	this->right_name = right_name;
	this->array = array;
	this->index = index;
	this->right = right;
}

void array_assignment::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}

void array_assignment::implement(){
	this->array->value[this->index->value].value = this->right->value;
	//this->name=this->left_name + " = " + std::to_string(this->right->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}



//---------------------------------------------------------

template <class Type>
lessthan<Type>::lessthan(std::string left_name, std::string right_name, Type* left, Type* right){
	this->name = left_name + " < " + right_name + ";";
	this->left_name = left_name;
	this->right_name = right_name;
	this->left = left;
	this->right = right;
}

template <class Type>
void lessthan<Type>::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}
template <class Type>
void lessthan<Type>::implement(){
	this->return_value=this->left->value < this->right->value ? true : false;
	//this->name=std::to_string(this->return_value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class lessthan<Variable<int> >;
//---------------------------------------------------------

template <class Type>
greaterthan<Type>::greaterthan(std::string left_name, std::string right_name, Type* left, Type* right){
	this->name = left_name + " > " + right_name + ";";
	this->left_name = left_name;
	this->right_name = right_name;
	this->left = left;
	this->right = right;
}

template <class Type>
void greaterthan<Type>::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}
template <class Type>
void greaterthan<Type>::implement(){
	this->return_value=this->left->value > this->right->value ? true : false;
	//cout << this->left->value << " > " << this->right->value << " ---> " << this->return_value << endl;
	//this->name=std::to_string(this->return_value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class greaterthan<Variable<int> >;
//---------------------------------------------------------

template <class Type>
multiply_and_assign<Type>::multiply_and_assign(std::string left_name, std::string right_name, Type* left, Type* right){
	this->name = left_name + " *= " + right_name + ";";
	this->left_name = left_name;
	this->right_name = right_name;
	this->left = left;
	this->right = right;
}

template <class Type>
void multiply_and_assign<Type>::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}
template <class Type>
void multiply_and_assign<Type>::implement(){
	//cout << this->left->value << "=" << this->left->value << "*" << this->right->value  << endl;
	this->left->value *= this->right->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class multiply_and_assign<Variable<int> >;
//---------------------------------------------------------

factorial::factorial(std::string left_name, std::string i_name, Variable<int>* left, Variable<int>* i){
	this->name = left_name + " = " + "factorial(" + i_name + ");";
	this->left_name = left_name;
	this->i_name = i_name;
	this->left = left;
	this->i = i;
}

void factorial::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}
/*
int factorial(int i){
	while(i>1)
	{
		result *= i;
		i++;
	}
	return result;
}
*/
void factorial::implement(){
	//int factorial(int i){
	NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
	Variable<int>* _i = new Variable<int>("i",this->i->value);
	NameSpace::active_stack->add_Variable( _i );
	Variable<int>* _result = new Variable<int>("result",1);
	NameSpace::active_stack->add_Variable( _result );
	PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
	int depth=0;
	//while(i>1)
	Variable<int>* deneme = new Variable<int>();
	deneme->value=1;
	PipeLine::active_pipeline->add_Command( new Command(depth, WHILE, new greaterthan< Variable<int> >("while(i",  "1)", _i, deneme) ) );
	//{
	PipeLine::active_pipeline->add_Command( new Command(++depth, OPEN_SCOPE) );
	//result *= i;
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, new multiply_and_assign< Variable<int> >("result", "i", _result, _i) ) );
	//i++;
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, new post_decrement("i", _i) ) );
	//}
	PipeLine::active_pipeline->add_Command( new Command(depth--, CLOSE_LOOP_SCOPE) );
	//return result
	PipeLine::active_pipeline->add_Command( new Command(depth, NORMAL, new returner<Variable<int>>("result", this->left, _result) ) );
	//-------------------
	//this->name=this->left_name + " = " + std::to_string(this->return_value);
	PipeLine::active_pipeline->commands[0]->is_current=true;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}
//---------------------------------------------------------
template <class Type>
returner<Type>::returner(std::string returned_name, Type* left, Type* right){
	this->name = "return " + returned_name + ";";
	this->returned_name = returned_name;
	this->left = left;
	this->right = right;
}

template <class Type>
void returner<Type>::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}

template <class Type>
void returner<Type>::implement(){
	this->left->value = this->right->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class returner<Variable<int> >;
//---------------------------------------------------------

post_increment::post_increment(std::string variable_name, Variable<int>* variable){
	this->name = variable_name + "++;";
	this->variable=variable;
}

void post_increment::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}

void post_increment::implement(){
	this->variable->value += 1;
	//this->name=this->variable_name + " = " + std::to_string(this->variable->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}
//---------------------------------------------------------

post_decrement::post_decrement(std::string variable_name, Variable<int>* variable){
	this->name = variable_name + "--;";
	this->variable=variable;
}

void post_decrement::display(int x, int y){
	glPushMatrix();
		//glColor3f(0.5, 0.5, 1.0);
		string text = this->name;
		RenderString(x,Height-(y+24),text);
	glPopMatrix();
}

void post_decrement::implement(){
	this->variable->value -= 1;
	//this->name=this->variable_name + " = " + std::to_string(this->variable->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}
//---------------------------------------------------------

user_defined1::user_defined1(){
	this->name="user_defined1";
}

void user_defined1::display(int x, int y){
	glPushMatrix();
		glColor3f(0.5, 0.5, 1.0);
		string text = this->name+"()";
		RenderString(x,Height-(y+24),text);
		
		// Additional work if there are parameters
		// glColor3f(0.87, 0.87, 0.87);
		// text=param1->name, param2->name...
		// RenderString(this->x,Height-(this->y+12),text);
		
		// glColor3f(0.5, 0.5, 1.0);
		// text = ")";
		// RenderString(x,Height-(y+24),text);
		
	glPopMatrix();
}

void user_defined1::implement(){
	this->name=this->name+"----done";
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

//---------------------------------------------------------

user_defined2::user_defined2(){
	this->name="user_defined2";
}

void user_defined2::display(int x, int y){
	glPushMatrix();
		glColor3f(0.5, 0.5, 1.0);
		string text = this->name+"()";
		RenderString(x,Height-(y+24),text);
		
		// Additional work if there are parameters
		// glColor3f(0.87, 0.87, 0.87);
		// text=param1->name, param2->name...
		// RenderString(this->x,Height-(this->y+12),text);
		
		// glColor3f(0.5, 0.5, 1.0);
		// text = ")";
		// RenderString(x,Height-(y+24),text);
		
	glPopMatrix();
}

#define ARR_SIZE 5
void user_defined2::implement(){
	int deneme[ARR_SIZE]={1,2,3,4,5};
	NameSpace::active_stack=new NameSpace(NameSpace::active_stack);
	NameSpace::active_stack->add_Variable( new Variable<int>("i",0) );
	NameSpace::active_stack->add_Variable( new Variable<int>("a",15) );
	NameSpace::active_stack->add_Variable( new Variable<int>("b",20) );
	NameSpace::active_stack->add_Variable( new Array<int>("deneme",deneme,ARR_SIZE) );
	PipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);
	PipeLine::active_pipeline->add_Command( new Command(0,0,new user_defined1()) );
	PipeLine::active_pipeline->add_Command( new Command(0,0,new user_defined1()) );
	PipeLine::active_pipeline->add_Command( new Command(0,1,new user_defined1()) );
	glutPostRedisplay();
	glFlush();
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
	this->display(this->x,this->y);
	glFlush();
}