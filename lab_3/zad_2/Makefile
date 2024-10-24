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
program_zad_2: program_zad_2.o 
	$(LOADER) $(OPT) program_zad_2.o -o program_zad_2


program_zad_2.o: program_zad_2.c 
	$(CCOMP) -c $(OPT) program_zad_2.c $(INC) 

clean:
	rm -f *.o program_zad_2
