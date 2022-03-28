CC=g++

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

run: clean all
	./$(OUTNAME) >> data.txt
	python main.py >> data.txt
	python charts.py < data.txt