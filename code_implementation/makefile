

all: code_Deque

code_Deque: code_implementation.o
	g++ -O0 -g -Wall -Wextra -pedantic -std=c++11  code_implementation.o -o code_Deque

code_implementation.o: code_implementation.cpp
	g++ -O0 -g -Wall -Wextra -pedantic -std=c++11 -c code_implementation.cpp

clean:
	rm -f *.o code_Deque

gdb: Deque
	gdb ./code_Deque

val: Deque
	valgrind ./code_Deque

valv: Deque
	valgrind -v ./code_Deque

pre: Deque
	g++ -O0 -g -Wall -std=c++11 -E -c code_Deque.cpp

test: code_Deque
	./code_Deque
