all: compiler coder
	#

compiler: compiler.cpp
	g++ -std=c++11 compiler.cpp -o compiler

run: compiler
	./compiler

coder: coder.cpp
	g++ -std=c++11 coder.cpp -o coder
	./coder


clean:
	rm *.o *.gch deneme
