CC=gcc
FLAGS=-Wall -g
HEADER=frequency.h
.PHONY: all clean 
all: frequency
frequency.o:frequency.c $(HEADER)
	$(CC) $(FLAGS) -c frequency.c

main.o: main.c $(HEADER)
	$(CC) $(FLAGS) -c main.c

frequency: frequency.o main.o
	$(CC) $(FLAGS) frequency.o main.o -o frequency
	
clean:
	rm  *.o frequency
	
	

