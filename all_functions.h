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

template <class Type>
class array_assignment : public Function{
	public:
		array_assignment(Array<Type>* array, Variable<int>* index, Variable<Type>* right);	
		~array_assignment(){}
		void display(int x, int y);
		void implement();

	private:
		Array<Type>* array;
		Variable<int>* index;
		Variable<Type>* right;
};

template <class Type>
class lessthan : public Function{
	public:
		lessthan(Type* left, Type* right);	
		~lessthan(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* right;
};

template <class Type>
class greaterthan : public Function{
	public:
		greaterthan(Type* left, Type* right);	
		~greaterthan(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* right;
};

template <class Type>
class addition : public Function{
	public:
		addition(Type* left, Type* a, Type* b);	
		~addition(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* a;
		Type* b;
};

template <class Type>
class subtraction : public Function{
	public:
		subtraction(Type* left, Type* a, Type* b);	
		~subtraction(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* a;
		Type* b;
};

template <class Type>
class multiplication : public Function{
	public:
		multiplication(Type* left, Type* a, Type* b);	
		~multiplication(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* a;
		Type* b;
};

template <class Type>
class division : public Function{
	public:
		division(Type* left, Type* a, Type* b);	
		~division(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* a;
		Type* b;
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

template <class Type>
class multiply_and_assign : public Function{
	public:
		multiply_and_assign(Type* left, Type* right);	
		~multiply_and_assign(){}
		void display(int x, int y);
		void implement();
		
	private:
		Type* left;
		Type* right;
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
