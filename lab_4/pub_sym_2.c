#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3
//pub_sym_2 -> bez zabezpieczen, sledzenie liczby kufli, wypisanie iloscina zakonczeniu symulacji
//klient to watek
void * watek_klient (void * arg);

int l_kf; //liczba kufli

int uzywany_kufel=0; 

//deklaracja mutexu
pthread_mutex_t mutex;

int main( void ){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kr, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);

  //inicjalizacja mutexu
  pthread_mutex_init(&mutex,NULL);
  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  l_kr = 1000000000; // wystarczajaco duzo, zeby nie bylo rywalizacji 

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;


  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nZamykamy pub!\n"); 
 // printf("Ilosc uzytych kufli: %d\n",uzywany_kufel);

  pthread_mutex_destroy(&mutex);


}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, j, kufel, result;
  int ile_musze_wypic = ILE_MUSZE_WYPIC;

  long int wykonana_praca = 0;

  printf("\nKlient %d, wchodze do pubu\n", moj_id); 
    
  for(i=0; i<ile_musze_wypic; i++){

    int sukces=0;

    printf("\nKlient %d, wybieram kufel\n", moj_id); 

    
  
  do{

    //zabezpieczamy dostep do zmiennej
    pthread_mutex_lock(&mutex);
    
    if(uzywany_kufel<l_kf){
        uzywany_kufel++;
        printf("\nAktualnie zuzyto %d kufli\n",uzywany_kufel);
        pthread_mutex_unlock(&mutex); //odblokowanie dostepu do zmiennej

        j=0;//nr kranu
        printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
        usleep(30);


        printf("\nKlient %d, pije\n", moj_id); 
        nanosleep((struct timespec[]){{0, 50000000L}}, NULL); //czeka 50ms, czas picia
        printf("\nKlient %d, odkladam kufel\n", moj_id); 

        // Zmniejszamy licznik używanych kufli
        pthread_mutex_lock(&mutex);
        uzywany_kufel--;
        pthread_mutex_unlock(&mutex);
        sukces=1;
    }
    else{
      pthread_mutex_unlock(&mutex);

      //brak dostepnych kufli, klient czeka
      int wait=rand() %100000;
      printf("\n Klient %d czeka %d ms na wolny kufel\n",moj_id,wait);
      usleep(wait);

      pthread_mutex_lock(&mutex);
      wykonana_praca++;
      pthread_mutex_unlock(&mutex);

      printf("\n Klient %d wykonana praca +1\n",moj_id);

      
    }
    
   } while(sukces==0); //powtarzaj dopoki nie zdobedziemy kufla
  }
  printf("\nKlient %d, wychodze z pubu; wykonana praca %ld\n",
	 moj_id, wykonana_praca); 
    
  return(NULL);
} 
