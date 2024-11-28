
CC = gcc
LD = gcc

OPT = -O3

INC = 
LIB = -pthread

bariera.o: bariera.c bariera.h
	$(CC) -c $(OPT) bariera.c $(INC)

main.o: main.c bariera.h
	$(CC) -c $(OPT) main.c $(INC)

main: main.o bariera.o
	$(LD) $(OPT) -o main main.o bariera.o $(LIB)

clean:
	rm -f *.o main bariera
