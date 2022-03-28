CC=g++

ifeq ($(OS), Winsows_NT)
	RM = del
else
	RM = rm -rf
endif

all: main angle

main: main.cpp
	$(CC) main.cpp -o main

angle: angle.cpp
	$(CC) angle.cpp -o angle

clean:
	$(RM) *.out *.o *.h.gch *.txt main angle

run: all
	./main 5 out
	./angle