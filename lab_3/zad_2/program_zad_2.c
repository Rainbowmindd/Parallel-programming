#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *funkcja_watku(void *arg) {
    
    int thread_id = *((int*) arg);// pobieranie thread id przekazanego jako argument

    printf("Watek:  id systemowy: %lu,   przekazane id: %d\n", pthread_self(), thread_id);

    //koniec watku
    pthread_exit(NULL);
}

int main() {
    int liczba_watkow = 5;
    pthread_t watki[liczba_watkow]; 
    int watki_id[liczba_watkow]; 

    int thread_id=0;
    //tworzenie watku w petli 
    for (int i = 0; i < liczba_watkow; i++) {  //zakres 0..liczba_watkow-1
        watki_id[i] = i; 
        if (pthread_create(&watki[i], NULL, funkcja_watku, &watki_id[i]) != 0) {
            printf("Blad tworzenia watku %d\n", i);
            return 1;
        }
    }

    //czekanie na zakonczenie wszystkich watkow
    for (int i = 0; i < liczba_watkow; i++) {
        pthread_join(watki[i], NULL);
    }

    printf("Zakonczenie dzialania wszystkich watkow.\n");
    return 0;
}
