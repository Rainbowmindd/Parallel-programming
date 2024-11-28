#ifndef _czytelnia_
#define _czytelnia_

#include <pthread.h>

/*** Definicje typow zmiennych ***/
typedef struct {
  int l_p;    // liczba piszacych
  int l_c;    // liczba czytajacych
  //nast zad
  pthread_mutex_t mutex;      // mutex do synchronizacji
  pthread_cond_t czytelnicy;  // zmienna warunku dla czytelnikow
  pthread_cond_t pisarze;     // zmienna warunku dla pisarzy
} cz_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(cz_t* czytelnia_p);
void czytam(cz_t* czytelnia_p);
void pisze(cz_t* czytelnia_p);

int my_read_lock_lock(cz_t* czytelnia_p);
int my_read_lock_unlock(cz_t* czytelnia_p);
int my_write_lock_lock(cz_t* czytelnia_p);
int my_write_lock_unlock(cz_t* czytelnia_p);

#endif
