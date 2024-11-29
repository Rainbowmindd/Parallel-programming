#include <pthread.h>
#include <stdio.h>

static int thread_count = 0;        // liczba wątków wymaganych do przejścia bariery
static int waiting_threads = 0;     //liczba wątków, które dotarły do bariery

static pthread_mutex_t barrier_mutex;   //mutex do ochrony sekcji krytycznej
static pthread_cond_t barrier_cond;     //zmienna warunku do sygnalizowania

void bariera_init(int threads){
    thread_count = threads;
   // waiting_threads = 0;
    pthread_mutex_init(&barrier_mutex, NULL);
    pthread_cond_init(&barrier_cond, NULL);
}
// wait*&nie_pelny,&muteks) usypiam watek i odblokowuje mu mutex, zwolnienie mutexa bez uzycia unlocka, argument &mutex uwalniany dla innego watku moze sobie wejsc
// signal -> ten co czeka zostanie wybudzony dopiero w momencie ktory moze zajac ten muteks
//broadcast-> wszystkie wybudzimy np 3 w sekcji kryczynej
//z waita wychodza po kolei, zajmuje muteks robi swoje rzecyz odblokowuje
//2 sekcje krytyczne lock-> wait, wait-> unlock


void bariera(void){
    pthread_mutex_lock(&barrier_mutex);

    waiting_threads++;

    if (waiting_threads < thread_count){
        pthread_cond_wait(&barrier_cond, &barrier_mutex);   //oczekiwanie na pozostałe watki, czeka na sygnal
    } else {
        //ostatni watek - reset licznika i budzi pozostale watki
        waiting_threads = 0;
        pthread_cond_broadcast(&barrier_cond);
    }

    pthread_mutex_unlock(&barrier_mutex);
}

void bariera_destroy(void){
    pthread_mutex_destroy(&barrier_mutex);
    pthread_cond_destroy(&barrier_cond);
}