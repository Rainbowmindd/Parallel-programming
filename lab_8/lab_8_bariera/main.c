#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "bariera.h"

extern void bariera_init(int);
extern void bariera(void);

#define LICZBA_W 4
//#define LICZBA_W 44

pthread_t watki[LICZBA_W];
void *cokolwiek( void *arg);


int main( int argc, char *argv[] ){

  int indeksy[LICZBA_W];
  for(int i = 0; i < LICZBA_W; i++) indeksy[i]=i; 

  //inicjalizacja bariery
  bariera_init(LICZBA_W);

  //tworzenie watkow
  for(int i = 0; i < LICZBA_W; i++ ) {
    pthread_create( &watki[i], NULL, cokolwiek, (void*) &indeksy[i] );
  }

  //czekanie na zakonczenie watkow
  for(int i = 0; i < LICZBA_W; i++ ) pthread_join(watki[i], NULL);

  // walnianie zasobow bariery
  bariera_destroy();

  pthread_exit(NULL);  
}


void* cokolwiek( void* arg){

  int moj_id = *(int*)arg;
  
  printf("przed bariera 1 - watek %d\n", moj_id);

  bariera();

  printf("przed bariera 2 - watek %d\n", moj_id);

  bariera();

  printf("przed bariera 3 - watek %d\n", moj_id);

  bariera();

  printf("przed bariera 4 - watek %d\n", moj_id);

  bariera();

  printf("po ostatniej barierze - watek %d\n",moj_id);  

  pthread_exit((void *)0);
}
