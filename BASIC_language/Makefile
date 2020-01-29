all: BASIC_language


BASIC_language: main.cpp arithmetic.o boolean.o command.o interpreter.o
	g++ -g -std=c++11 -Wall main.cpp arithmetic.o boolean.o command.o interpreter.o -o hw4

arithmetic.o: arithmetic.h arithmetic.cpp 
	g++ -g -std=c++11  -Wall -c arithmetic.cpp -o arithmetic.o 

boolean.o: boolean.h boolean.cpp
	g++ -g -std=c++11  -Wall -c boolean.cpp -o boolean.o 

command.o: command.h command.cpp
	g++ -g -std=c++11  -Wall -c command.cpp -o command.o 

interpreter.o: interpreter.h interpreter.cpp
	g++ -g -std=c++11 -Wall -c interpreter.cpp -o interpreter.o
