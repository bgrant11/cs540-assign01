

all: Deque

Deque: test.o
	g++ -O0 -g -Wall -std=c++11  test.o -o Deque

test.o: test.cpp
	g++ -O0 -g -Wall -std=c++11 -c test.cpp

clean:
	rm -f *.o Deque

gdb: Deque
	gdb ./Deque

val: Deque
	valgrind ./Deque

valv: Deque
	valgrind -v ./Deque
