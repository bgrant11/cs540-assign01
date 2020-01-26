all: play

play: main.o
	g++ -O0 -g -Wall -std=c++11  main.o -o play

code_implementation.o: main.cpp
	g++ -O0 -g -Wall -std=c++11 -c main.cpp

clean:
	rm -f *.o play


test: play
	./play
