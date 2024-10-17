#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>


int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{

  zmienna_globalna++;

//zajecia 2 wypisuje dane
    char arg1[] = "./zajecia2"; // Ścieżka do programu
    char arg2[] = "Martyna Kindrat"; // Argument
    char *arg[] = {arg1, arg2, NULL}; // Tablica argumentów

    int wynik=execv(arg[0],arg);
//wywolanie programu za pomoca execv
 //  int wynik; 
 //  wynik=execv("./program",NULL); 
   if(wynik==-1) {
   printf("Proces potomny nie wykonal programu\n"); }

  return 0;
}

int main()
{

  void *stos;
  pid_t pid;
  int i; 

  inicjuj_czas(); //pomiar start
  
 

  for(i=0;i<1000;i++){

    //alokacja stosu dla kazdego watku
    stos = malloc( ROZMIAR_STOSU );

    if (stos == 0) {
      printf("Proces nadrzędny - blad alokacji stosu\n");
      exit( 1 );
    }

    //tworzneie watku przy pomocy clone
    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );

    waitpid(pid, NULL, __WCLONE); //oczekiwanie na zakonczenie watku
    free( stos );
  }

  return 0;
}
