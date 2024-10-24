#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

#define ROZMIAR_STOSU 1024 * 64
int zmienna_globalna=0;

int funkcja_watku(void *argument) {
     int zmienna_lokalna = *((int*) argument); 

    for(int i=0;i<100000;i++){
        zmienna_globalna++;
        zmienna_lokalna++;
    }
    printf("Koniec pracy watku: \n Zmienna globalna: %d\n Zmienna lokalna:  %d\n",zmienna_globalna,zmienna_lokalna);

    return 0;
}

int main() {
    void *stos1, *stos2; //stosy dla watkow
    pid_t pid1, pid2;  //watek ID
 
    //alokacja stosu watek 1
    stos1 = malloc(ROZMIAR_STOSU);
    //alokacja stosu watek 2
    stos2 = malloc(ROZMIAR_STOSU);
    if(stos1 ==NULL || stos2 == NULL) {
        printf("Blad alokacji stosu dla watku\n");
        exit(1);
    }
    int zmienna_lokalna1=0;
    int zmienna_lokalna2=0;

    //tworzenie watku1
    pid1 = clone(funkcja_watku, (void *)stos1 + ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna_lokalna1);
    if (pid1 == -1) { //jeśli pid==-1 sygnał że tworzenie watku nie powiodło się
        printf("Blad tworzenia watku \n");
        free(stos1);
        free(stos2);
        exit(1);
    }

    //tworzenie watku2
    pid2 = clone(funkcja_watku, (void *)stos2 + ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM,&zmienna_lokalna2);
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
    printf("Koniec pracy OBU wątkow \nZmienna globalna: %d\n Zmienna lokalna1: %d\n Zmienna lokalna2: %d\n",zmienna_globalna,zmienna_lokalna1,zmienna_lokalna2);

   //free memory
    free(stos1);
    free(stos2);

    return 0;
}
