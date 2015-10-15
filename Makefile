CC=g++
CFLAGS=-c -Wall -std=c++11

all: puzzlesolver

puzzlesolver: main.o search_tree.o
	$(CC) main.o search_tree.o -o puzzlesolver

main.o: main.cc
	$(CC) $(CFLAGS) main.cc

search_tree.o: search_tree.cc
	$(CC) $(CFLAGS) search_tree.cc

clean:
	rm *o puzzlesolver

