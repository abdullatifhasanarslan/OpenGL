#ifndef ALL_FUNCTIONS_H
#define ALL_FUNCTIONS_H
#include "Functions.h"
#include "Variables.h"

//FUNCTIONS ARE DECLARED HERE
// template <class Type>
// class combined : public Function{
// 	public:
// 		combined(Function* left, Function* function, Function* right);	
// 		~combined(){}
// 		void display(int x, int y);
// 		void implement();

// 	private:
// 		Function* left;
// 		void* function;
// 		Function* right;
// };

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

class factorial : public Function{
	public:
		factorial(Variable<int>* left, Variable<int>* i);	
		~factorial(){}
		void display(int x, int y);
		void implement();
		int result;
		Variable<int>* i;
		
	private:
		Variable<int>* left;
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

class user_defined1 : public Function{
	public:
		user_defined1();	
		~user_defined1(){}	
		void display(int x, int y);
		void implement();	
};

class user_defined2 : public Function{
	public:
		user_defined2();
		~user_defined2(){}	
		void display(int x, int y);
		void implement();				
};

class user_defined3 : public Function{
	public:
		user_defined3();
		~user_defined3(){}	
		void display(int x, int y);
		void implement();		
};

class user_defined4 : public Function{
	public:
		user_defined4();
		~user_defined4(){}	
		void display(int x, int y);
		void implement();		
};

class user_defined5 : public Function{
	public:
		user_defined5();
		~user_defined5(){}	
		void display(int x, int y);
		void implement();		
};

class user_defined6 : public Function{
	public:
		user_defined6();
		~user_defined6(){}	
		void display(int x, int y);
		void implement();		
};

class user_defined7 : public Function{
	public:
		user_defined7();
		~user_defined7(){}	
		void display(int x, int y);
		void implement();		
};

class user_defined8 : public Function{
	public:
		user_defined8();
		~user_defined8(){}	
		void display(int x, int y);
		void implement();				
};
class user_defined9 : public Function{
	public:
		user_defined9();
		~user_defined9(){}
		void display(int x, int y);
		void implement();				
};
class user_defined10 : public Function{
	public:
		user_defined10(int k, int l, int m);
		~user_defined10(){}
		void display(int x, int y);
		void implement();				
	private:
		int r;
		int g;
		int b;
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