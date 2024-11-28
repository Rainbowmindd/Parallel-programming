#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "czytelnia.h"

/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(cz_t* cz_p) {
    cz_p->l_c++;
    
    // Sprawdzamy poprawność liczby czytelników i pisarzy
    if (cz_p->l_p < 0 || cz_p->l_c < 0 || cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0)) {
        printf("Blad: niepoprawna liczba pisarzy (%d) lub czytelników (%d)!\n", cz_p->l_p, cz_p->l_c);
        exit(0);
    }
    
    // Wydruk kontrolny
    printf("\t\t\t\t\tczytelnicy i pisarze: l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);
    return 0;
}

int my_read_lock_unlock(cz_t* cz_p) {
    cz_p->l_c--;
    
    // Sprawdzamy poprawność liczby czytelników i pisarzy
    if (cz_p->l_p < 0 || cz_p->l_c < 0 || cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0)) {
        printf("Blad: niepoprawna liczba pisarzy (%d) lub czytelników (%d)!\n", cz_p->l_p, cz_p->l_c);
        exit(0);
    }
    
    // Wydruk kontrolny
    printf("\t\t\t\t\tczytelnicy i pisarze: l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);
    return 0;
}

int my_write_lock_lock(cz_t* cz_p) {
    cz_p->l_p++;
    
    // Sprawdzamy poprawność liczby czytelników i pisarzy
    if (cz_p->l_p < 0 || cz_p->l_c < 0 || cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0)) {
        printf("Blad: niepoprawna liczba pisarzy (%d) lub czytelników (%d)!\n", cz_p->l_p, cz_p->l_c);
        exit(0);
    }
    
    // Wydruk kontrolny
    printf("\t\t\t\t\tczytelnicy i pisarze: l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);
    return 0;
}

int my_write_lock_unlock(cz_t* cz_p) {
    cz_p->l_p--;
    
    // Sprawdzamy poprawność liczby czytelników i pisarzy
    if (cz_p->l_p < 0 || cz_p->l_c < 0 || cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0)) {
        printf("Blad: niepoprawna liczba pisarzy (%d) lub czytelników (%d)!\n", cz_p->l_p, cz_p->l_c);
        exit(0);
    }
    
    // Wydruk kontrolny
    printf("\t\t\t\t\tczytelnicy i pisarze: l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);
    return 0;
}

void inicjuj(cz_t* cz_p) {
    cz_p->l_p = 0;
    cz_p->l_c = 0;
}

void czytam(cz_t* cz_p) {
    // Sprawdzamy poprawność liczby czytelników i pisarzy
    if (cz_p->l_p < 0 || cz_p->l_c < 0 || cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0)) {
        printf("Blad: niepoprawna liczba pisarzy (%d) lub czytelników (%d)!\n", cz_p->l_p, cz_p->l_c);
        exit(0);
    }
    
    printf("\t\t\t\t\tczytam: l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);
    usleep(rand() % 3000000);
}

void pisze(cz_t* cz_p) {
    // Sprawdzamy poprawność liczby czytelników i pisarzy
    if (cz_p->l_p < 0 || cz_p->l_c < 0 || cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0)) {
        printf("Blad: niepoprawna liczba pisarzy (%d) lub czytelników (%d)!\n", cz_p->l_p, cz_p->l_c);
        exit(0);
    }
    
    printf("\t\t\t\t\tpisze: l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);
    usleep(rand() % 3000000);
}
