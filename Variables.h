#ifndef VARIABLES_H
#define VARIABLES_H
#include <string>
#include <map>
#include <vector>

using namespace std;
class entity{
	public:
		static int last_pose=0;
		static std::vector<entity*> all_variables;
		virtual void display() = 0;
		entity(int x, int y, int width, int height);
		void move(int x, int y);
		void setPose(int x, int y);
		bool checkCollision(int x, int y);
	private:
		int X, Y, WIDTH, HEIGHT;
		int x, y, width, height;
	protected:

}
template <class Type>
class Variable : public entity {
	//static int last_pos=0;
	public:
		std::string name;		//remember to make this const
		Type value;
		Variable(std::string name, Type value);
		Variable(const Variable<Type> &object);	//copy constructor
		void display();
		//assignment-----------------------------------------------------------------------------
		Variable<Type>& operator=(const Variable<Type>& operand);		//simp-assignment:	a=b
		Variable<Type>& operator+=(const Variable<Type>& operand);		//add-assignment:	a+=b
		Variable<Type>& operator-=(const Variable<Type>& operand);		//sub-assignment:	a-=b
		Variable<Type>& operator*=(const Variable<Type>& operand);		//mul-assignment:	a*=b
		Variable<Type>& operator/=(const Variable<Type>& operand);		//div-assignment:	a/=b
		Variable<Type>& operator%=(const Variable<Type>& operand);		//mod-assignment:	a%=b
		Variable<Type>& operator&=(const Variable<Type>& operand);		//AND-assignment:	a&=b
		Variable<Type>& operator|=(const Variable<Type>& operand);		//OR-assignment:	a|=b
		Variable<Type>& operator^=(const Variable<Type>& operand);		//XOR-assignent:	a^=b
		Variable<Type>& operator<<=(const Variable<Type>& operand);		//lsh-assignent:	a<<=b
		Variable<Type>& operator>>=(const Variable<Type>& operand);		//rsh-assignent:	a>>=b							//pointomemofpoint:	a->*b
		//logical--------------------------------------------------------------------------------
		Variable<bool> operator!() const;											//negation:			!a
		Variable<bool> operator&&(const Variable<Type>& operand) const;			//AND:				a&&b
		Variable<bool> operator||(const Variable<Type>& operand) const;			//OR:				a||b
		//comparison-----------------------------------------------------------------------------
		Variable<bool> operator==(const Variable<Type>& operand) const;	//equal:			a==b
		Variable<bool> operator!=(const Variable<Type>& operand) const;	//notequal:			a!=b
		Variable<bool> operator<(const Variable<Type>& operand) const;	//lessthan:			a<b
		Variable<bool> operator>(const Variable<Type>& operand) const;	//greaterthan:		a>b
		Variable<bool> operator<=(const Variable<Type>& operand) const;	//lesseqthan:		a<=b
		Variable<bool> operator>=(const Variable<Type>& operand) const;	//greateqthan:		a>=b
		//			  operator<=>(const Variable<Type>& operand) const;	//threewaycomp:		a<=>b
		//arithmetic-----------------------------------------------------------------------------
		Variable<Type> operator+() const;								//unary plus:		+a
		Variable<Type> operator-() const;								//unary minus:		-a
		Variable<Type> operator+(const Variable<Type>& operand) const;	//addition:			a+b
		Variable<Type> operator-(const Variable<Type>& operand) const;	//subtracion:		a-b
		Variable<Type> operator*(const Variable<Type>& operand) const;	//multiplication:	a*b
		Variable<Type> operator/(const Variable<Type>& operand) const;	//division:			a/b
		Variable<Type> operator%(const Variable<Type>& operand) const;	//modulo:			a%b
		//increment-decrement--------------------------------------------------------------------
		Variable<Type> operator++();									//pre-increment:	++a
		Variable<Type> operator--();									//pre-decrement:	--a
		//Variable<Type> operator++(int);								//post-increment:	a++
		//Variable<Type> operator--(int);								//post-decrement:	a--
		//member access--------------------------------------------------------------------------
		/*
		template <class ReType, class InType>
		Variable<ReType>& operator[](InType index);						//subscript:		a[b]
		Variable<ReType>& operator*();									//indirection:		*a
		Variable<ReType>& operator&();									//addressof:		&a
		Variable<ReType>& operator->();									//memberofpointer:	a->b
		Variable<ReType>& operator->*();									//post-decrement:	a--
		*/
		~Variable();
		template <class T>
		friend std::ostream& operator<<(std::ostream& out, const Variable<T>& variable);
	private:
		//int X, Y;
		//int WIDTH, HEIGHT;
	protected:
	
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