
deneme:	deneme.o events.o Variables.o Functions.o all_functions.o
	g++ deneme.o events.o Variables.o Functions.o all_functions.o -lGL -lGLU -lglut -lm -o deneme
# deneme:	deneme.o events.o utility.o Variables.o Functions.o all_functions.o
# 	g++ deneme.o events.o Variables.o Functions.o all_functions.o -lGL -lGLU -lglut -lm -o deneme
# utility.o: 	utility.h utility.cpp
# 	g++ utility.h utility.cpp -Wall -Werror -c 

deneme.o: 	deneme.cpp models.h Variables.h
	g++ deneme.cpp models.h Variables.h -Wall -Werror -c
events.o: 	events.h events.cpp Variables.h
	g++ events.h events.cpp Variables.h -Wall -Werror -c 

Variables.o:	Variables.h Variables.cpp models.h
	g++ -std=c++11 Variables.h Variables.cpp models.h -Wall -Werror -c
Functions.o:	Functions.h Functions.cpp
	g++ -std=c++11 Functions.h Functions.cpp  -Wall -Werror -c

all_functions.o: 	all_functions.h all_functions.cpp
	g++ -std=c++11 all_functions.h all_functions.cpp -Wall -Werror -c

clean:
	rm *.o *.gch deneme
