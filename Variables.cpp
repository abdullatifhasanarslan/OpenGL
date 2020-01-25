#include <iostream>
#include "Variables.h"
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;
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

//-----------------------------------------------------------
template <class Type>
Variable<Type>::Variable(std::string name, Type value){
	this->name=name;
	this->value=value;
	this->width=200;
	this->height=50;
}
template <>
Variable<bool>::Variable(std::string name, bool value){
	this->name=name;
	this->value=value;
	this->width=50;
	this->height=50;
}
template <>
Variable<int>::Variable(std::string name, int value){
	this->name=name;
	this->value=value;
	this->width=value;
	this->height=50;
}
template <class Type>
Variable<Type>::Variable(const Variable<Type> &object){
	this->name="<blank>";
	this->value=object.value;
}

template <class Type>
void Variable<Type>::display(){
	glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.7, 0.7, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(this->x,this->y);
			glVertex2d(this->x,this->y+this->height);
			glVertex2d(this->x+this->width,this->y+this->height);
			glVertex2d(this->x+this->width,this->y);
		glEnd();
	glPopMatrix();
}

template <class Type>
void Variable<Type>::setPose(int x, int y){
	this->x=x;
	this->y=y;
}

template <class Type>
bool Variable<Type>::checkCollision(int x, int y){
	cout  << this->name << ":  " << this->x << "," << this->y << "----" << x << "," << y << endl;
	if(this->x<x && x<this->x+this->width && this->y<y && y<this->y+this->height){
		cout << "a" << endl;
		return true;
	}
	return false;
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