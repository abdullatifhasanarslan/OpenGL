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
assignment< Type >::assignment(Type* left, Type* right){
	this->left = left;
	this->right = right;
}

template <class Type>
void assignment<Type>::display(int x, int y){
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


array_assignment::array_assignment(Array<int>* array, Variable<int>* index, Variable<int>* right){
	this->array = array;
	this->index = index;
	this->right = right;
}

void array_assignment::display(int x, int y){
}

void array_assignment::implement(){
	this->array->value[this->index->value].value = this->right->value;
	//this->name=this->left_name + " = " + std::to_string(this->right->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}



//---------------------------------------------------------

template <class Type, class Type2>
lessthan<Type,Type2>::lessthan(Type* left, Type2* right){
	this->left = left;
	this->right = right;
}

template <class Type, class Type2>
void lessthan<Type,Type2>::display(int x, int y){
}

template <class Type, class Type2>
void lessthan<Type,Type2>::implement(){
	this->return_value=this->left->value < this->right->value ? true : false;
	//this->name=std::to_string(this->return_value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class lessthan<Variable<int>, Variable<int> >;
//---------------------------------------------------------

template <class Type, class Type2>
greaterthan<Type,Type2>::greaterthan(Type* left, Type2* right){
	this->left = left;
	this->right = right;
}

template <class Type, class Type2>
void greaterthan<Type,Type2>::display(int x, int y){
}
template <class Type, class Type2>
void greaterthan<Type,Type2>::implement(){
	this->return_value=this->left->value > this->right->value ? true : false;
	//cout << this->left->value << " > " << this->right->value << " ---> " << this->return_value << endl;
	//this->name=std::to_string(this->return_value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class greaterthan<Variable<int>, Variable<int>>;
//---------------------------------------------------------

template <class Type, class Type2>
multiply_and_assign<Type,Type2>::multiply_and_assign(Type* left, Type2* right){
	this->left = left;
	this->right = right;
}

template <class Type,class Type2>
void multiply_and_assign<Type,Type2>::display(int x, int y){
}
template <class Type,class Type2>
void multiply_and_assign<Type,Type2>::implement(){
	//cout << this->left->value << "=" << this->left->value << "*" << this->right->value  << endl;
	this->left->value *= this->right->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class multiply_and_assign<Variable<int>,Variable<int> >;
//---------------------------------------------------------

//---------------------------------------------------------
template <class Type>
returner<Type>::returner(Type* left, Type* right){
	this->left = left;
	this->right = right;
}

template <class Type>
void returner<Type>::display(int x, int y){
}

template <class Type>
void returner<Type>::implement(){
	if(this->left!=NULL){
		this->left->value = this->right->value;
	}
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class returner<Variable<int> >;
//---------------------------------------------------------

post_increment::post_increment(Variable<int>* variable){
	this->variable=variable;
}

void post_increment::display(int x, int y){
}

void post_increment::implement(){
	this->variable->value += 1;
	//this->name=this->variable_name + " = " + std::to_string(this->variable->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}
//---------------------------------------------------------

post_decrement::post_decrement(Variable<int>* variable){
	this->variable=variable;
}

void post_decrement::display(int x, int y){
}

void post_decrement::implement(){
	this->variable->value -= 1;
	//this->name=this->variable_name + " = " + std::to_string(this->variable->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}
//---------------------------------------------------------

modulo::modulo(Variable<int>* left, Variable<int>* right){
	this->left = left;
	this->right = right;
}

void modulo::display(int x, int y){
	glPushMatrix();
	glPopMatrix();
}
void modulo::implement(){
	this->result=this->left->value % this->right->value;
	this->return_value=this->result>0 ? true:false;
	//cout << this->left->value << " > " << this->right->value << " ---> " << this->return_value << endl;
	//this->name=std::to_string(this->return_value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}
