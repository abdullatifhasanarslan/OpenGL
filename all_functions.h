#ifndef ALL_FUNCTIONS_H
#define ALL_FUNCTIONS_H
#include "Functions.h"
#include "Variables.h"

//FUNCTIONS ARE DECLARED HERE

template <class Type>
class assignment : public Function{
	public:
		assignment(Type* left, Type* right);	
		~assignment(){}
		void display(int x, int y);
		void implement();

	private:
		Type* left;
		Type* right;
};

class array_assignment : public Function{
	public:
		array_assignment(Array<int>* array, Variable<int>* index, Variable<int>* right);	
		~array_assignment(){}
		void display(int x, int y);
		void implement();

	private:
		Array<int>* array;
		Variable<int>* index;
		Variable<int>* right;
};

template <class Type, class Type2>
class lessthan : public Function{
	public:
		lessthan(Type* left, Type2* right);	
		~lessthan(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* right;
};

template <class Type, class Type2>
class greaterthan : public Function{
	public:
		greaterthan(Type* left, Type2* right);	
		~greaterthan(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type2* right;
};

template <class Type>
class returner : public Function{
	public:
		returner(Type* left, Type* right);	
		~returner(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* right;
};

template <class Type,class Type2>
class multiply_and_assign : public Function{
	public:
		multiply_and_assign(Type* left, Type2* right);	
		~multiply_and_assign(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type2* right;
};


class post_increment : public Function{
	public:
		post_increment(Variable<int>* variable);	
		~post_increment(){}	
		void display(int x, int y);
		void implement();
		Variable<int>* variable;
		
	private:
};

class post_decrement : public Function{
	public:
		post_decrement(Variable<int>* variable);	
		~post_decrement(){}	
		void display(int x, int y);
		void implement();
		Variable<int>* variable;
		
	private:
};

class modulo : public Function{
	public:
		modulo(Variable<int>* left, Variable<int>* right);	
		~modulo(){}
		void display(int x, int y);
		void implement();
		int result;
	private:
		Variable<int>* left;
		Variable<int>* right;
};



#endif