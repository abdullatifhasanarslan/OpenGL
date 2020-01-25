#ifndef VARIABLES_H
#define VARIABLES_H
#include <string>
#include <map>

using namespace std;
template <class Type>
class Variable{
	//static int last_pos=0;
	public:
		std::string name;		//remember to make this const
		Type value;
		Variable(std::string name, Type value);
		~Variable();
		template <class T>
		friend std::ostream& operator<<(std::ostream& out, const Variable<T>& variable);
		Variable<Type> operator+(const Variable<Type>& added) const;
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

//+ 	- 	* 	/

//double number=3.4345;
//number=1.618;
//double number1=number2;
//number1=number2;
//number1==number2;
//number1 +,-,*,/,= number,variable


//int number=3;
//number=1;
//int number1=number2;
//number1=number2;
//number1==number2;
//number1 +,-,*,/,= number,variable

class NameSpace{
	public:
		NameSpace();
		~NameSpace();
		void* get_Variable(const std::string name);
		void add_Variable(const void* const variable);
		friend std::ostream& operator<<(std::ostream& out, const NameSpace& name_space);
	private:
		NameSpace* parent;
		std::map<std::string,void*> names;
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