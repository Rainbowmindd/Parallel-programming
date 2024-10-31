#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3
//pub_sym_0 -> bez zabezpieczen, sledzenie liczby kufli, wypisanie iloscina zakonczeniu symulacji
//klient to watek
void * watek_klient (void * arg);

int l_kf; //liczba kufli
// int aktualnie_uzywany_kufel=0; 
// int zuzyte_kufle_symulacja=0;
int dostepne_kufle; //zmienna wspolna dla wszystkich watkow

//mutexy przed petla i po 1 kran 

pthread_mutex_t mutex;

int main( void ){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kr, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);

  dostepne_kufle=l_kf;

  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
   l_kr = 1; // wystarczajaco duzo, zeby nie bylo rywalizacji 

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;

//inicjalizacja mutexu
  pthread_mutex_init(&mutex,NULL);

  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", dostepne_kufle); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nZamykamy pub!\n"); 
  printf("Zostalo %d kufli\n",dostepne_kufle);

  if(dostepne_kufle!=l_kf){ //porownanie ynikow
    printf("\nZmiana poczatkowej liczby kufli: z %d na %d\n",l_kf,dostepne_kufle);
  }

  pthread_mutex_destroy(&mutex);


}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, j, kufel, result;
  int ile_musze_wypic = ILE_MUSZE_WYPIC;

  long int wykonana_praca = 0;

  pthread_mutex_lock(&mutex);

  printf("\nKlient %d, wchodze do pubu\n", moj_id); 

 
  for(i=0; i<ile_musze_wypic; i++){

    printf("\nKlient %d, wybieram kufel\n", moj_id); 
    usleep(1);
  
        dostepne_kufle--;

        if (dostepne_kufle<0) {
            printf("\nBlad: klient %d pobral kufel mimo BRAKU wolnych kufli\n", moj_id);
        }

        //printf("\nAktualnie zuzyto %d kufli\n",dostepne_kufle);

          j=0;//nr kranu
          printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
           usleep(30);


        printf("\nKlient %d, pije\n", moj_id); 
         nanosleep((struct timespec[]){{0, 50000000L}}, NULL);
    
        printf("\nKlient %d, odkladam kufel\n", moj_id); 

        dostepne_kufle++;

    }

    pthread_mutex_unlock(&mutex);
    
  

  printf("\nKlient %d, wychodze z pubu; wykonana praca %ld\n",
	 moj_id, wykonana_praca); 
    
  return(NULL);
} 

