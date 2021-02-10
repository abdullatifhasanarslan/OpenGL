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
template class assignment<Variable<float> >;
template class assignment<Variable<char> >;
//---------------------------------------------------------


template <class Type>
array_assignment<Type>::array_assignment(Array<Type>* array, Variable<int>* index, Variable<Type>* right){
	this->array = array;
	this->index = index;
	this->right = right;
}

template <class Type>
void array_assignment<Type>::display(int x, int y){
}

template <class Type>
void array_assignment<Type>::implement(){
	this->array->value[this->index->value].value = this->right->value;
	//this->name=this->left_name + " = " + std::to_string(this->right->value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}


template class array_assignment<int>;
template class array_assignment<float>;
template class array_assignment<char>;

//---------------------------------------------------------

template <class Type>
addition<Type>::addition(Type* left, Type* a, Type* b){
	this->left = left;
	this->a = a;
	this->b = b;
}

template <class Type>
void addition<Type>::display(int x, int y){
}
template <class Type>
void addition<Type>::implement(){
	this->left->value=this->a->value + this->b->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class addition<Variable<int>>;
template class addition<Variable<float>>;
template class addition<Variable<char>>;

//---------------------------------------------------------

template <class Type>
subtraction<Type>::subtraction(Type* left, Type* a, Type* b){
	this->left = left;
	this->a = a;
	this->b = b;
}

template <class Type>
void subtraction<Type>::display(int x, int y){
}
template <class Type>
void subtraction<Type>::implement(){
	this->left->value=this->a->value - this->b->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class subtraction<Variable<int>>;
template class subtraction<Variable<float>>;
template class subtraction<Variable<char>>;

//---------------------------------------------------------

template <class Type>
multiplication<Type>::multiplication(Type* left, Type* a, Type* b){
	this->left = left;
	this->a = a;
	this->b = b;
}

template <class Type>
void multiplication<Type>::display(int x, int y){
}
template <class Type>
void multiplication<Type>::implement(){
	this->left->value=this->a->value * this->b->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class multiplication<Variable<int>>;
template class multiplication<Variable<float>>;
template class multiplication<Variable<char>>;


//---------------------------------------------------------

template <class Type>
division<Type>::division(Type* left, Type* a, Type* b){
	this->left = left;
	this->a = a;
	this->b = b;
}

template <class Type>
void division<Type>::display(int x, int y){
}
template <class Type>
void division<Type>::implement(){
	this->left->value=this->a->value / this->b->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class division<Variable<int>>;
template class division<Variable<float>>;
template class division<Variable<char>>;


//---------------------------------------------------------

template <class Type>
lessthan<Type>::lessthan(Type* left, Type* right){
	this->left = left;
	this->right = right;
}

template <class Type>
void lessthan<Type>::display(int x, int y){
}

template <class Type>
void lessthan<Type>::implement(){
	this->return_value=this->left->value < this->right->value;
	//this->name=std::to_string(this->return_value);
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class lessthan<Variable<int>>;
template class lessthan<Variable<float>>;
template class lessthan<Variable<char>>;
//---------------------------------------------------------

template <class Type>
greaterthan<Type>::greaterthan(Type* left, Type* right){
	this->left = left;
	this->right = right;
}

template <class Type>
void greaterthan<Type>::display(int x, int y){
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

template class greaterthan<Variable<int>>;
template class greaterthan<Variable<float>>;
template class greaterthan<Variable<char>>;
//---------------------------------------------------------

template <class Type>
multiply_and_assign<Type>::multiply_and_assign(Type* left, Type* right){
	this->left = left;
	this->right = right;
}

template <class Type>
void multiply_and_assign<Type>::display(int x, int y){
}
template <class Type>
void multiply_and_assign<Type>::implement(){
	//cout << this->left->value << "=" << this->left->value << "*" << this->right->value  << endl;
	this->left->value *= this->right->value;
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class multiply_and_assign<Variable<int>>;
template class multiply_and_assign<Variable<float>>;
template class multiply_and_assign<Variable<char>>;
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
	}else{
		exit(0);
	}
	this->display(this->x,this->y);
	glutPostRedisplay();
	glFlush();
}

template class returner<Variable<int> >;
template class returner<Variable<float>>;
template class returner<Variable<char>>;
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
