CC=g++
CFLAGS=-c -Wall

ifeq ($(OS), Winsows_NT)
	RM = del
else
	RM = rm -rf
endif

all: main

main: main.o math.o utils.o
	$(CC) main.o math.o utils.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

math.o: math.cpp
	$(CC) $(CFLAGS) math.h math.cpp

utils.o: utils.cpp
	$(CC) $(CFLAGS) utils.h utils.cpp

clean:
	$(RM) *.o *.h.gch main

run: all
	./main 0 0 1 1