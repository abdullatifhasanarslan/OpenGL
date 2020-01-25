#include <iostream>
#include "Variables.h"

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
}
template <class Type>
Variable<Type>::~Variable(){

}
template <class Type>
Variable<Type> Variable<Type>::operator+(const Variable<Type>& added) const{
	return Variable<Type>("NULL",this->value+added.value);
}


template class Variable<char>;
template class Variable<double>;
template class Variable<float>;
template class Variable<int>;