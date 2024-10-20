#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

#define ROZMIAR_STOSU 1024 * 64
#define LICZBA_ITERACJI 100000

int zmienna_globalna=0;

//5. nowy program na podstawie clone.c
int funkcja_watku(void *argument) {
    
}

int main() {
    void *stos1, *stos2; //stosy dla watkow
    pid_t pid1, pid2;  //watek ID
     
 
    //alokacja stosu watek 1
    stos1 = malloc(ROZMIAR_STOSU);
    if(stos1 == NULL) {
        printf("Blad alokacji stosu dla watku\n");
        exit(1);
    } 

    //alokacja stosu watek 2
    stos2 = malloc(ROZMIAR_STOSU);
    if(stos2 == NULL) {
        printf("Blad alokacji stosu dla watku\n");
        free(stos1);
        exit(1);
    }

    //tworzenie watku1
    pid1 = clone(funkcja_watku, (void *)stos1 + ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    if (pid1 == -1) {
        printf("Blad tworzenia watku \n");
        free(stos1);
        free(stos2);
        exit(1);
    }

    //tworzenie watku2
    pid2 = clone(funkcja_watku, (void *)stos2 + ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    if(pid2 == -1) {
        printf("Blad tworzenia watku \n");
        free(stos1);
        free(stos2);
        exit(1);
    }

    //czekanie na zakonczenie dwoch watkow
    waitpid(pid1, NULL, __WCLONE);
    waitpid(pid2, NULL, __WCLONE);

    //po zakonczeniu pracy
    printf("Koniec pracy watkow \n");

   //free memory
    free(stos1);
    free(stos2);

    return 0;
}
