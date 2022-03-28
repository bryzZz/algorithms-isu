CC=g++
CFLAGS=-c -Wall -std=c++2a

ifeq ($(OS), Winsows_NT)
	RM = del
	OUTNAME = main.exe
else
	RM = rm -rf
	OUTNAME = main
endif

all:
	$(CC) main.cpp -o $(OUTNAME)

clean:
	$(RM) *.out *.o *.h.gch *.txt $(OUTNAME)

run: all
	./$(OUTNAME) > out.txt
	python3.8 main.py < out.txt