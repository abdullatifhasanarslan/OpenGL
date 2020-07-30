#ifndef ALL_FUNCTIONS_H
#define ALL_FUNCTIONS_H
#include "Functions.h"
#include "Variables.h"

//FUNCTIONS ARE DECLARED HERE
template <class Type>
class assignment : public Function{
	public:
		assignment(std::string left_name, std::string right_name, Type* left, Type* right);	
		void display(int x, int y);
		void implement();
		bool return_value;

	private:
		std::string left_name;
		std::string right_name;
		Type* left;
		Type* right;
};

template <class Type>
class lessthan : public Function{
	public:
		lessthan(std::string left_name, std::string right_name, Type* left, Type* right);	
		void display(int x, int y);
		void implement();
		bool return_value;
		
	private:
		std::string left_name;
		std::string right_name;
		Type* left;
		Type* right;
};

template <class Type>
class greaterthan : public Function{
	public:
		greaterthan(std::string left_name, std::string right_name, Type* left, Type* right);	
		void display(int x, int y);
		void implement();
		bool return_value;
		
	private:
		std::string left_name;
		std::string right_name;
		Type* left;
		Type* right;
};

template <class Type>
class multiply_and_assign : public Function{
	public:
		multiply_and_assign(std::string left_name, std::string right_name, Type* left, Type* right);	
		void display(int x, int y);
		void implement();
		
	private:
		std::string left_name;
		std::string right_name;
		Type* left;
		Type* right;
};

class factorial : public Function{
	public:
		factorial(std::string left_name, std::string i_name, Variable<int>* left, Variable<int>* i);	
		void display(int x, int y);
		void implement();
		int return_value;
		Variable<int>* i;
		
	private:
		std::string left_name;
		std::string i_name;
		Variable<int>* left;
};

class post_increment : public Function{
	public:
		post_increment(std::string variable_name, Variable<int>* variable);	
		void display(int x, int y);
		void implement();
		Variable<int>* variable;
		
	private:
		std::string variable_name;
};

class user_defined1 : public Function{
	public:
		user_defined1();	
		void display(int x, int y);
		void implement();	
};

class user_defined2 : public Function{
	public:
		user_defined2();
		void display(int x, int y);
		void implement();				
};

class user_defined3 : public Function{
	public:
		user_defined3();
		void display(int x, int y);
		void implement();		
};

class user_defined4 : public Function{
	public:
		user_defined4();
		void display(int x, int y);
		void implement();		
};

class user_defined5 : public Function{
	public:
		user_defined5();
		void display(int x, int y);
		void implement();		
};

class user_defined6 : public Function{
	public:
		user_defined6();
		void display(int x, int y);
		void implement();		
};

class user_defined7 : public Function{
	public:
		user_defined7();
		void display(int x, int y);
		void implement();		
};

class user_defined8 : public Function{
	public:
		user_defined8();
		void display(int x, int y);
		void implement();				
};
class user_defined9 : public Function{
	public:
		user_defined9();
		void display(int x, int y);
		void implement();				
};
class user_defined10 : public Function{
	public:
		user_defined10(int k, int l, int m);
		void display(int x, int y);
		void implement();				
	private:
		int r;
		int g;
		int b;
};


#endif