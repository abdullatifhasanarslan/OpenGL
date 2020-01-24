#include <iostream>
#include "Variables.h"

using namespace std;

NameSpace::NameSpace(){

}

NameSpace::~NameSpace(){

}

Variable* NameSpace::get_Variable(const std::string name){
	return NULL;
}

void NameSpace::add_Variable(const Variable* const variable){

}

std::ostream& operator<<(std::ostream& out, const NameSpace& name_space) {
    return out;
}

//-----------------------------------------------------------
Variable::Variable(std::string name){
	this->name=name;
}

Variable::~Variable(){

}

std::ostream& operator<<(std::ostream& out, const Variable& variable) {
    out << variable.name;
    return out;
}

//-----------------------------------------------------------
Char::Char(std::string name, char value) : Variable(name){
	this->value=value;
}

Char::~Char(){

}

std::ostream& operator<<(std::ostream& out, const Char& variable) {
    out << variable.name << "=" << variable.value;
    return out;
}

//-----------------------------------------------------------
Double::Double(std::string name, double value) : Variable(name){
	this->value=value;
}

Double::~Double(){

}

std::ostream& operator<<(std::ostream& out, const Double& variable) {
    out << variable.name << "=" << variable.value;
    return out;
}
//-----------------------------------------------------------
Float::Float(std::string name, float value) : Variable(name){
	this->value=value;
}

Float::~Float(){

}

std::ostream& operator<<(std::ostream& out, const Float& variable) {
    out << variable.name << "=" << variable.value;
    return out;
}
//-----------------------------------------------------------
Int::Int(std::string name, int value) : Variable(name){
	this->value=value;
}

Int::~Int(){

}

std::ostream& operator<<(std::ostream& out, const Int& variable) {
    out << variable.name << "=" << variable.value;
    return out;
}
//-----------------------------------------------------------
Pointer::Pointer(std::string name, void* value) : Variable(name){
	this->value=value;
}

Pointer::~Pointer(){

}

std::ostream& operator<<(std::ostream& out, const Pointer& variable) {
    out << variable.name << "=" << variable.value;
    return out;
}
