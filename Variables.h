#ifndef VARIABLES_H
#define VARIABLES_H
#include <string>
#include <map>

using namespace std;

class Variable{
	//static int last_pos=0;
	public:
		std::string name;		//remember to make this const
		Variable(std::string name);
		~Variable();		
		friend std::ostream& operator<<(std::ostream& out, const Variable& variable);
	private:

	protected:
		//int X, Y;
		//int x, y;
		//int WIDTH, HEIGHT;
		//int width, height;
	
};
//char character='a';
//character='a';
//char character1=character2;
//character1=character2;
//character ==,+,-,*,/,= number,character

class Char: public Variable{
	public:
		char value;
		Char(std::string name, char value);
		~Char();
		friend std::ostream& operator<<(std::ostream& out, const Char& variable);
	
	private:
	protected:
};

//double number=3.4345;
//number=1.618;
//double number1=number2;
//number1=number2;
//number1==number2;
//number1 +,-,*,/,= number,variable
class Double: public Variable{
	public:
		double value;
		Double(std::string name, double value);
		~Double();
		friend std::ostream& operator<<(std::ostream& out, const Double& variable);
	private:
	protected:
};

//float number=3.4345;
//number=1.618;
//float number1=number2;
//number1=number2;
//number1==number2;
//number1 +,-,*,/,= number,variable
class Float: public Variable{
	public:
		float value;
		Float(std::string name, float value);
		~Float();
		friend std::ostream& operator<<(std::ostream& out, const Float& variable);
	private:
	protected:
};

//int number=3;
//number=1;
//int number1=number2;
//number1=number2;
//number1==number2;
//number1 +,-,*,/,= number,variable
class Int: public Variable{
	public:
		int value;
		Int(std::string name, int value);
		~Int();
		friend std::ostream& operator<<(std::ostream& out, const Int& variable);
	private:
	protected:
};

class Pointer: public Variable{
	public:
		void* value;
		Pointer(std::string name, void* value);
		~Pointer();
		friend std::ostream& operator<<(std::ostream& out, const Pointer& variable);
	private:
	protected:
};

class NameSpace{
	public:
		NameSpace();
		~NameSpace();
		Variable* get_Variable(const std::string name);
		void add_Variable(const Variable* const variable);
		friend std::ostream& operator<<(std::ostream& out, const NameSpace& name_space);
	private:
		NameSpace* parent;
		std::map<std::string,Variable*> names;
	protected:
};
#endif

/*
auto       break    case     char     const     continue
default    do       double   else     enum      extern
float      for      goto     if       int       long
register   return   short    signed   sizeof    static
struct     switch   typedef  union    unsigned  void
volatile   while 

+ 	- 	* 	/ 		% 		^
& 	| 	~ 	! 		, 		=
< 	> 	<= 	>= 		++ 		--
<< 	>> 	== 	!= 		&& 		||
+= 	-= 	/= 	%= 		^= 		&=
|= 	*= 	<<= >>= 	[] 		()
-> 	->* new new[] 	delete 	delete[]
*/