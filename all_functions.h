#ifndef ALL_FUNCTIONS_H
#define ALL_FUNCTIONS_H
#include "Functions.h"

//FUNCTIONS ARE DECLARED HERE

template <class Type>
class assignment : public Function{
	public:
		assignment(std::string left_name, std::string right_name, Type* left, Type* right);	
		void display(int x, int y);
		void implement();

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
		
	private:
		std::string left_name;
		std::string right_name;
		Type* left;
		Type* right;
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