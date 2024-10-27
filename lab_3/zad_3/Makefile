# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
struktura: struktura.o 
	$(LOADER) $(OPT) struktura.o -o struktura


struktura.o: struktura.c 
	$(CCOMP) -c $(OPT) struktura.c $(INC) 

clean:
	rm -f *.o struktura
