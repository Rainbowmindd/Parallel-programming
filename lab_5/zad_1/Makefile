# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3 -fopenmp

# pliki naglowkowe
INC = -I../../pomiar_czasu

# biblioteki
LIB = -L../../pomiar_czasu -lpomiar_czasu -lm -lpthread
# LIB = -L./lib -lpomiar_czasu -lm -lpthread

# zaleznosci i komendy
pthreads_suma: pthreads_suma.o pomiar_czasu.o
	$(LOADER) $(OPT) pthreads_suma.o -o pthreads_suma $(LIB)

pthreads_suma.o: pthreads_suma.c ../../pomiar_czasu/pomiar_czasu.h  
	$(CCOMP) -c $(OPT) pthreads_suma.c $(INC)

pomiar_czasu.o: ../../pomiar_czasu/pomiar_czasu.c ../../pomiar_czasu/pomiar_czasu.h  
	$(CCOMP) -c $(OPT) ../../pomiar_czasu/pomiar_czasu.c $(INC)
clean:
	rm -f *.o pthreads_suma pomiar_czasu.o