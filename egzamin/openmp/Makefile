CCOMP = /usr/bin/mpicc

LOADER = /usr/bin/mpicc

MPIRUN = /usr/bin/mpiexec 

OPT = -O2 -fopenmp

LIB =  -lm

all: test

test: test.o
	$(LOADER) $(OPT) test.o -o test $(LIB)

test.o: test.c
	$(CCOMP) -c $(OPT) test.c $(INC)

run:
	$(MPIRUN) -np $(NUM_THREADS) --oversubscribe  ./test
	
clean:
	rm -f *.o ./test