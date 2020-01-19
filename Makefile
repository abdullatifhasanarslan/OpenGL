
deneme:	deneme.o events.o
	g++ deneme.o events.o control.o -lGL -lGLU -lglut -lm -o deneme

deneme.o: deneme.cpp models.h
	g++ deneme.cpp models.h -c -Wall -Werror
events.o: events.h events.cpp
	g++ events.h events.cpp -Wall -Werror -c 
control.o: Variables.h Functions.h
	g++ Variables.h Functions.h -Wall -Werror -c

clean:
	rm *.o deneme
