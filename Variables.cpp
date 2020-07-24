#include <iostream>
#include "Variables.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "utility.h"

using namespace std;
extern GLubyte fly[];
extern GLubyte halftone[];
extern GLubyte something[];
extern int Width;
extern int Height;
extern void RenderString(int x, int y, const std::string &string, void* font=GLUT_BITMAP_TIMES_ROMAN_24);

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
int entity::getwidth(){
	return this->width;
}

int entity::getheight(){
	return this->height;
}

//-----------------------------------------------------------

template <class Type>
Variable<Type>::Variable(){
	this->setSize(200,50);
}

template <class Type>
Variable<Type>::Variable(std::string name, Type value){
	this->name=name;
	this->value=value;
	this->setSize(200,50);
}
template <>
Variable<bool>::Variable(std::string name, bool value){
	this->name=name;
	this->value=value;
	this->setSize(50,50);
}
template <>
Variable<char>::Variable(std::string name, char value){
	this->name=name;
	this->value=value;
	this->setSize(50,50);
}
template <>
Variable<int>::Variable(std::string name, int value){
	this->name=name;
	this->value=value;
	this->setSize(value,50);
}
template <>
Variable<float>::Variable(std::string name, float value){
	this->name=name;
	this->value=value;
	this->setSize(value,50);
}
template <>
Variable<double>::Variable(std::string name, double value){
	this->name=name;
	this->value=value;
	this->setSize(value,50);
}
template <>
Variable<Variable<int>*>::Variable(std::string name, Variable<int>* value){
	this->name=name;
	this->value=value;
	this->setSize(12,50);
}
template <class Type>
Variable<Type>::Variable(const Variable<Type> &object){
	this->name="<blank>";
	this->value=object.value;
	this->setSize(object.width,object.height);
}

template <class Type>
Array<Type>::Array(std::string name, Type* value, int length){
	this->length=length;
	this->name=name;
	this->value = new Variable<Type>[this->length];
	for(int i=0;i<length;i++){
		this->value[i].value=value[i];
	}
	this->setSize(25,50);
}

template <class Type>
void Variable<Type>::display(int x, int y){
	this->x=x;
	this->y=y;
	glPushMatrix();
		glColor3f(0.4, 0.4, 1.0);
		string text = std::to_string(this->value);
		RenderString(this->x,Height-(this->y),text);
		text=this->name+"="+text;
		RenderString(this->x,Height-(this->y+12),text,GLUT_BITMAP_HELVETICA_12);
	glPopMatrix();
}

template <>
void Variable<char>::display(int x, int y){
	this->x=x;
	this->y=y;
	glPushMatrix();
		glColor3f(0.7, 0.7, 0.0);
		string text(1,this->value);
		RenderString(this->x,Height-(this->y),text);
		text=this->name+"="+text;
		RenderString(this->x,Height-(this->y+12),text,GLUT_BITMAP_HELVETICA_12);
	glPopMatrix();
}

template <>
void Variable<bool>::display(int x, int y){
	this->x=x;
	this->y=y;
	glPushMatrix();
		(this->value ? glColor3f(0.0, 0.7, 0.0) : glColor3f(0.7, 0.0, 0.0));
		string text = this->value ? "true" : "false";
		RenderString(this->x,Height-(this->y),text);
		text=this->name+"="+text;
		RenderString(this->x,Height-(this->y+12),text,GLUT_BITMAP_HELVETICA_12);
		
	glPopMatrix();
}


//pointer
template <>
void Variable<Variable<int>*>::display(int x, int y){
	this->x=x;
	this->y=y;
	glPushMatrix();
		glColor3f(0.8, 0.4, 0.0);
		glLineWidth(2.0);
		string text = "*";
		RenderString(this->x,Height-(this->y),text);
		text=this->name+"=&"+this->value->name;
		RenderString(this->x,Height-(this->y+12),text,GLUT_BITMAP_HELVETICA_12);		
		glLineWidth(1.0);
		Line(this->x,Height-(this->y),this->value->x,Height-(this->value->y));
	glPopMatrix();
}

//array

template <class Type>
void Array<Type>::display(int x, int y){
	this->x=x;
	this->y=y;
	int font_height=24;
	int element_height=this->value[0].getheight();
	int last_pose=y;
	glPushMatrix();

		glLineWidth(1.0);
		for(int i=0;i<this->length;i++){
			Line(this->x-10,Height-(last_pose-element_height),this->x+30,Height-(last_pose-element_height));
			Line(this->x-10,Height-(last_pose-element_height),this->x-10,Height-(last_pose+font_height));
			Line(this->x-10,Height-(last_pose+font_height),this->x+30,Height-(last_pose+font_height));
			this->value[i].display(x,last_pose);
			last_pose+=element_height+font_height;
		}
		last_pose-=element_height;

	glPopMatrix();
}

//structs should be defined here

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
//member accss--------------------------------------------------------------------------
template <class Type>
Variable<Type>& Array<Type>::operator[](int index){
	return this->value[index];
}
/*
template <class Type>
Variable<Variable<Type>*>& Variable<Variable<Type>*>::operator*(){
	return this->value->value;
}
template <class Type>
Variable<Variable<Type>*>& Variable<Variable<Type>*>::operator&(){
	return this;
}
*/
/*
Variable<Variable<Type>*>& operator->(){
	return this;
}
Variable<ReType>& operator->*();								//pointomemofpoint:	a->*b
template <class ReType, class InType>
Variable<ReType>& operator[](InType index);						//subscript:		a[b]
*/

template <class Type>
Variable<Type>::~Variable(){

}
template <class Type>
Array<Type>::~Array(){
	delete[] this->value;
}
template class Variable<char>;
template class Variable<double>;
template class Variable<float>;
template class Variable<int>;
template class Variable<bool>;
template class Array<int>;
//template class Variable<void*>;

//---------------------------------------------------------------------------------------
NameSpace::NameSpace(){
	this->parent=NULL;
}

NameSpace::NameSpace(NameSpace* parent){
	this->parent=parent;
}

NameSpace::~NameSpace(){

}

entity* NameSpace::get_Variable(const std::string name){
	return NULL;
}

NameSpace* NameSpace::get_parent(){
	return this->parent;
}

void NameSpace::add_Variable(entity*  variable){
	this->names[variable->name]=variable;
	this->ordered.push_back(variable);
}

std::ostream& operator<<(std::ostream& out, const NameSpace& name_space) {
    return out;
}