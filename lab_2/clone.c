#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
#include "../pomiar_czasu/pomiar_czasu.h"


int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku(void* argument) {
    zmienna_globalna++; 

    char* arg[] = {"./zajecia2", "Martyna", "Kindrat", NULL}; 
    int wynik = execv(arg[0], arg); 
    if (wynik == -1) {
        printf("Proces potomny nie wykonal programu\n"); 
    }

    return 0;
}


int main()
{

  void *stos;
  pid_t pid;
  int i; 

  
  //alokacja stosu dla kazdego watku
    stos = malloc( ROZMIAR_STOSU );

    if (stos == 0) {
      printf("Proces nadrzędny - blad alokacji stosu\n");
      exit( 1 );
    }

    inicjuj_czas(); //pomiar start

  for(i=0;i<1000;i++){

    //tworzneie watku przy pomocy clone
    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );

    waitpid(pid, NULL, __WCLONE); //oczekiwanie na zakonczenie watku
    
  }
  drukuj_czas();
free( stos );
  return 0;
}
