
deneme:	deneme.o events.o Variables.o Functions.o
	g++ deneme.o events.o Variables.o Functions.o -lGL -lGLU -lglut -lm -o deneme

deneme.o: deneme.cpp models.h
	g++ deneme.cpp models.h -Wall -Werror -c
events.o: events.h events.cpp
	g++ events.h events.cpp -Wall -Werror -c 

Variables.o: Variables.h Variables.cpp
	g++ Variables.h Variables.cpp -Wall -Werror -c
Functions.o: Functions.h Functions.cpp
	g++ Functions.h Functions.cpp -Wall -Werror -c

clean:
	rm *.o *.gch deneme
