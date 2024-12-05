#include <pthread.h>
#include <stdio.h>


int liczba_czyt=0;
int liczba_pisz=0;

static pthread_cond_t czytelnicy;
static pthread_cond_t pisarze;

static pthreads_mutex_t mutex;

void chce_pisac(){
    pthread_mutex_lock(&mutex);
    if(liczba_czyt+liczba_pisz>0){
        pthread_cond_wait(&pisarze, &mutex);
    }
    liczba_pisz++;

}
