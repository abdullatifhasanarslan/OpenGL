#include <iostream>
#include "Variables.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

using namespace std;
extern GLubyte fly[];
extern GLubyte halftone[];
extern GLubyte something[];
entity::entity(){
	// this->X=x;
	// this->Y=y;
	// this->WIDTH=width;
	// this->HEIGHT=height;
}

entity::~entity(){
	std::cerr << "There is something here my friend" << endl;
}

void entity::move(int x, int y){
	this->x=x;
	this->y=y;
}

void entity::setPose(int x, int y){
	this->x=x;
	this->y=y;
}

void entity::setSize(int width, int height){
	this->width=width;
	this->height=height;
}

bool entity::checkCollision(int x, int y){
	//cout  << this->name << ":  " << this->x << "," << this->y << "----" << x << "," << y << endl;
	cout  << this->x << "," << this->y << "----" << x << "," << y << endl;
	if(this->x<x && x<this->x+this->width && this->y<y && y<this->y+this->height){
		return true;
	}
	return false;
}

int entity::getx(){
	return this->x;
}

int entity::gety(){
	return this->y;
}

//-----------------------------------------------------------
template <class Type>
Variable<Type>::Variable(std::string name, Type value){
	this->name=name;
	this->value=value;
	this->setPose(0,0);
	this->setSize(200,50);
	entity::all_variables.push_back(this);
}
template <>
Variable<bool>::Variable(std::string name, bool value){
	this->name=name;
	this->value=value;
	this->setPose(500,100);
	this->setSize(50,50);
	entity::all_variables.push_back(this);
}
template <>
Variable<int>::Variable(std::string name, int value){
	this->name=name;
	this->value=value;
	this->setPose(0,300);
	this->setSize(value,50);
	entity::all_variables.push_back(this);
}
template <class Type>
Variable<Type>::Variable(const Variable<Type> &object){
	this->name="<blank>";
	this->value=object.value;
	this->setPose(object.x,object.y);
	this->setSize(object.width,object.height);
	entity::all_variables.push_back(this);
}

template <class Type>
void Variable<Type>::display(){
	glPushMatrix();
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonStipple(fly);
		glColor3f(0.7, 0.7, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(this->x,this->y);
			glVertex2d(this->x,this->y+this->height);
			glVertex2d(this->x+this->width,this->y+this->height);
			glVertex2d(this->x+this->width,this->y);
		glEnd();
		glDisable(GL_POLYGON_STIPPLE);
	glPopMatrix();
}

template <>
void Variable<char>::display(){
	glPushMatrix();
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonStipple(something);
		glColor3f(0.7, 0.7, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(this->x,this->y);
			glVertex2d(this->x,this->y+this->height);
			glVertex2d(this->x+this->width,this->y+this->height);
			glVertex2d(this->x+this->width,this->y);
		glEnd();
		glDisable(GL_POLYGON_STIPPLE);
	glPopMatrix();
}

template <>
void Variable<bool>::display(){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		(this->value ? glColor3f(0.0, 0.7, 0.0) : glColor3f(0.7, 0.0, 0.0));
		glBegin(GL_POLYGON);
			glVertex2d(this->x,this->y);
			glVertex2d(this->x,this->y+this->height);
			glVertex2d(this->x+this->width,this->y+this->height);
			glVertex2d(this->x+this->width,this->y);
		glEnd();
	glPopMatrix();
}

//assignment-----------------------------------------------------------------------------
template <class Type>
Variable<Type>& Variable<Type>::operator=(const Variable<Type>& operand){
	this->value=operand.value;
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator+=(const Variable<Type>& operand){
	this->value+=operand.value;
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator-=(const Variable<Type>& operand){
	this->value-=operand.value;
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator*=(const Variable<Type>& operand){
	this->value*=operand.value;
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator/=(const Variable<Type>& operand){
	this->value/=operand.value;
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator%=(const Variable<Type>& operand){
	return *this;
}
template <>
Variable<int>& Variable<int>::operator%=(const Variable<int>& operand){
	this->value%=operand.value;
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator&=(const Variable<Type>& operand){
	this->value&=operand.value;
	return *this;
}
template <>
Variable<double>& Variable<double>::operator&=(const Variable<double>& operand){
	return *this;
}
template <>
Variable<float>& Variable<float>::operator&=(const Variable<float>& operand){
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator|=(const Variable<Type>& operand){
	this->value|=operand.value;
	return *this;
}
template <>
Variable<double>& Variable<double>::operator|=(const Variable<double>& operand){
	return *this;
}
template <>
Variable<float>& Variable<float>::operator|=(const Variable<float>& operand){
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator^=(const Variable<Type>& operand){
	this->value^=operand.value;
	return *this;
}
template <>
Variable<double>& Variable<double>::operator^=(const Variable<double>& operand){
	return *this;
}
template <>
Variable<float>& Variable<float>::operator^=(const Variable<float>& operand){
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator<<=(const Variable<Type>& operand){
	this->value<<=operand.value;
	return *this;
}
template <>
Variable<double>& Variable<double>::operator<<=(const Variable<double>& operand){
	return *this;
}
template <>
Variable<float>& Variable<float>::operator<<=(const Variable<float>& operand){
	return *this;
}
template <class Type>
Variable<Type>& Variable<Type>::operator>>=(const Variable<Type>& operand){
	this->value>>=operand.value;
	return *this;
}
template <>
Variable<double>& Variable<double>::operator>>=(const Variable<double>& operand){
	return *this;
}
template <>
Variable<float>& Variable<float>::operator>>=(const Variable<float>& operand){
	return *this;
}
//logical--------------------------------------------------------------------------------
template <class Type>
Variable<bool> Variable<Type>::operator!() const{
	return Variable<bool>("<blank>",!this->value);
}
template <class Type>
Variable<bool> Variable<Type>::operator&&(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value && operand.value);
}
template <class Type>
Variable<bool> Variable<Type>::operator||(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value || operand.value);
}
template <class Type>
//comparison-----------------------------------------------------------------------------
Variable<bool> Variable<Type>::operator==(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value == operand.value);
}
template <class Type>
Variable<bool> Variable<Type>::operator!=(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value != operand.value);
}
template <class Type>
Variable<bool> Variable<Type>::operator<(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value < operand.value);
}
template <class Type>
Variable<bool> Variable<Type>::operator>(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value > operand.value);
}
template <class Type>
Variable<bool> Variable<Type>::operator<=(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value <= operand.value);
}
template <class Type>
Variable<bool> Variable<Type>::operator>=(const Variable<Type>& operand) const{
	return Variable<bool>("<blank>",this->value >= operand.value);
}
//			  operator<=>(const Variable<Type>& operand) const;	//threewaycomp:		a<=>b
//arithmetic-----------------------------------------------------------------------------
template <class Type>
Variable<Type> Variable<Type>::operator+() const{
	return Variable<Type>("<blank>",this->value);
}
template <class Type>
Variable<Type> Variable<Type>::operator-() const{
	return Variable<Type>("<blank>",this->value);
}
template <class Type>
Variable<Type> Variable<Type>::operator+(const Variable<Type>& operand) const{
	return Variable<Type>("<blank>",this->value + operand.value);
}
template <class Type>
Variable<Type> Variable<Type>::operator-(const Variable<Type>& operand) const{
	return Variable<Type>("<blank>",this->value - operand.value);
}
template <class Type>
Variable<Type> Variable<Type>::operator*(const Variable<Type>& operand) const{
	return Variable<Type>("<blank>",this->value * operand.value);
}
template <class Type>
Variable<Type> Variable<Type>::operator/(const Variable<Type>& operand) const{
	return Variable<Type>("<blank>",this->value / operand.value);
}
template <class Type>
Variable<Type> Variable<Type>::operator%(const Variable<Type>& operand) const{
	return *this;
}
template <>
Variable<int> Variable<int>::operator%(const Variable<int>& operand) const{
	return Variable<int>("<blank>",this->value % operand.value);
}
//increment-decrement--------------------------------------------------------------------
template <class Type>
Variable<Type> Variable<Type>::operator++(){
	++this->value;
	return Variable<Type>("<blank>",this->value);
}
template <>
Variable<bool> Variable<bool>::operator++(){
	return Variable<bool>("<blank>",this->value);
}
template <class Type>
Variable<Type> Variable<Type>::operator--(){
	--this->value;
	return Variable<Type>("<blank>",this->value);
}
template <>
Variable<bool> Variable<bool>::operator--(){
	return Variable<bool>("<blank>",this->value);
}
/*
Variable<Type> Variable<Type>::operator++(int){
	return Variable<Type>("<blank>",++this->value);
}
Variable<Type> Variable<Type>::operator--(int){
	return Variable<Type>("<blank>",--this->value);
}
*/
//member access--------------------------------------------------------------------------
/*
template <class ReType, class InType>
Variable<ReType>& operator[](InType index);						//subscript:		a[b]
Variable<ReType>& operator*();									//indirection:		*a
Variable<ReType>& operator&();									//addressof:		&a
Variable<ReType>& operator->();									//memberofpointer:	a->b
Variable<ReType>& operator->*();								//pointomemofpoint:	a->*b
*/

template <class Type>
Variable<Type>::~Variable(){

}
template class Variable<char>;
template class Variable<double>;
template class Variable<float>;
template class Variable<int>;
template class Variable<bool>;
//template class Variable<void*>;

//---------------------------------------------------------------------------------------
NameSpace::NameSpace(){

}

NameSpace::~NameSpace(){

}

void* NameSpace::get_Variable(const std::string name){
	return NULL;
}

void NameSpace::add_Variable(const void* const variable){

}

std::ostream& operator<<(std::ostream& out, const NameSpace& name_space) {
    return out;
}