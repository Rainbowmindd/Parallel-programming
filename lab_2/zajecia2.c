#include <stdio.h>
#include <unistd.h> //getpid()

int main(int argc, char *argv[]) {
    printf("Wywolany program:\n");

    const char *imie="Martyna";
    const char *nazwisko="Kindrat";
    pid_t nr_procesu=getpid(); //pobieranie procesu


    printf("Wywolany program:\n");
    for (int i = 0; i < argc; i++) {
        printf(" %d: %s\n", i, argv[i]);
    }

    printf("Imie: %s\n", imie);
    printf("Nazwisko: %s\n", nazwisko);
    printf("Numer procesu (PID): %d\n", nr_procesu); 
    
    return 0;
}
