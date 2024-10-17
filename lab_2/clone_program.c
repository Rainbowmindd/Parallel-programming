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
    //przekazana jako argument
    int *zmienna_lokalna = (int *)argument; 

    //zwiekszanie lokalnej i globalnej zmiennej
    for(int i = 0; i < LICZBA_ITERACJI; i++) {
        zmienna_globalna++;
        (*zmienna_lokalna)++;
    }

    printf("Watek -> koniec. Zmienna globalna: %d, zmienna lokalna: %d\n", zmienna_globalna, *zmienna_lokalna);
    return 0;
}

int main() {
    void *stos1, *stos2; //stosy dla watkow
    pid_t pid1, pid2;  //watek ID
    int zmienna_lokalna1 = 0;  //dla watku1
    int zmienna_lokalna2 = 0; //dla watku2

    //alokacja stosu watek 1
    stos1 = malloc(ROZMIAR_STOSU);
    if(stos1 == NULL) {
        printf("Blad alokacji stosu dla watku 1\n");
        exit(1);
    } 

    //alokacja stosu watek 2
    stos2 = malloc(ROZMIAR_STOSU);
    if(stos2 == NULL) {
        printf("Blad alokacji stosu dla watku 2\n");
        free(stos1);
        exit(1);
    }

    //tworzenie watku1
    pid1 = clone(funkcja_watku, (void *)stos1 + ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna_lokalna1);
    if (pid1 == -1) {
        printf("Blad tworzenia watku 1\n");
        free(stos1);
        free(stos2);
        exit(1);
    }

    //tworzenie watku2
    pid2 = clone(funkcja_watku, (void *)stos2 + ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna_lokalna2);
    if(pid2 == -1) {
        printf("Blad tworzenia watku 2\n");
        free(stos1);
        free(stos2);
        exit(1);
    }

    //czekanie na zakonczenie dwoch watkow
    waitpid(pid1, NULL, __WCLONE);
    waitpid(pid2, NULL, __WCLONE);

    //po zakonczeniu pracy
    printf("\nKoniec pracy watkow: \n");
    printf("Zmienna globalna: %d\n", zmienna_globalna);
    printf("Zmienna lokalna watek 1: %d\n", zmienna_lokalna1);
    printf("Zmienna lokalna watek 2: %d\n", zmienna_lokalna2);

   //free memory
    free(stos1);
    free(stos2);

    return 0;
}
