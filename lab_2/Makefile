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
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# zaleznosci i komendy
clone: clone.o 
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c 
	$(CCOMP) -c $(OPT) clone.c $(INC) 

#5. dodanie nowego programu 
clone_program: clone_program.o
	$(LOADER) $(OPT) clone_program.o -o clone_program $(LIB)

clone_program.o: clone_program.c 
	$(CCOMP) -c $(OPT) clone_program.c $(INC)

clean:
	rm -f *.o fork clone clone_program
