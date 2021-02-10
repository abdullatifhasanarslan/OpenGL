
deneme: deneme.o events.o Variables.o Functions.o all_functions.o 
	g++ deneme.o events.o Variables.o Functions.o all_functions.o -lGL -lGLU -lglut -lm -o deneme

deneme.o: user_defined deneme.cpp models.h Variables.h
	g++ -std=c++11 deneme.cpp models.h Variables.h -Wall -Werror -c
events.o: 	events.h events.cpp Variables.h
	g++ -std=c++11 events.h events.cpp Variables.h -Wall -Werror -c 

Variables.o:	Variables.h Variables.cpp models.h
	g++ -std=c++11 Variables.h Variables.cpp models.h -Wall -Werror -c
Functions.o:	Functions.h Functions.cpp
	g++ -std=c++11 Functions.h Functions.cpp  -Wall -Werror -c

all_functions.o: 	all_functions.h all_functions.cpp
	g++ -std=c++11 all_functions.h all_functions.cpp -Wall -Werror -c

compiler: compiler.cpp code.c
	g++ -std=c++11 compiler.cpp -o compiler

coder: coder.cpp sample_result.json
	g++ -std=c++11 coder.cpp -o coder

user_defined: coder compiler
	./compiler
	./coder

clean:
	rm *.o *.gch deneme compiler coder
