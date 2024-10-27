#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int zmienna_wspolna=0;

#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];



double czasozajmowacz(){
  int i, j, k;
  int n=WYMIAR;
  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i; 
  for(i=0;i<ROZMIAR;i++) b[i]=1.0*(ROZMIAR-i);

  //#M mnozenie macierzy
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      c[i+n*j]=0.0;
      for(k=0;k<n;k++){
	c[i+n*j] += a[i+n*k]*b[k+n*j];
      }
    }
  }
  return(c[ROZMIAR-1]);  //Zwrócenie ostatniego elementu macierzy c
}

void * zadanie_watku (void * arg_wsk)
{
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	printf("\twatek potomny: uniemozliwione zabicie\n");

	czasozajmowacz(); 

	printf("\twatek potomny: umozliwienie zabicia\n");
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	pthread_testcancel();

	zmienna_wspolna++;
	printf("\twatek potomny: zmiana wartosci zmiennej wspolnej\n");


	return(NULL);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	void *wynik;
	int i;

	// Wątek przyłączalny
	
	printf("watek glowny: tworzenie watku potomnego nr 1\n");

	/*Tu wstaw kod tworzenia watkuu z domyslnymi wlasciwosciami*/
    pthread_create(&tid,NULL,zadanie_watku,NULL); //watek1

	sleep(2); // czas na uruchomienie watku

	printf("\twatek glowny: wyslanie sygnalu zabicia watku\n");
	pthread_cancel(tid);

	//Co nalezy zrobic przed sprawdzeniem czy watki sie skonczyly?
    //trzeba poczekac na zakonczenie watku
    pthread_join(tid,&wynik);

	if (wynik == PTHREAD_CANCELED) 
		printf("\twatek glowny: watek potomny zostal zabity\n");
	else
		printf("\twatek glowny: watek potomny NIE zostal zabity - blad\n");

	//Odlaczanie watku
	zmienna_wspolna = 0; //reset zmiennej

	printf("watek glowny: tworzenie watku potomnego nr 2\n");

	/*Tu wstaw kod tworzenia watku z domyslnymi wlasciwosciami*/
    pthread_create(&tid,NULL,zadanie_watku,NULL); //watek2

	sleep(2); // czas na uruchomienie watku

	printf("\twatek glowny: odlaczenie watku potomnego\n");
	//Instrukcja oodlaczenia?
    pthread_detach(tid);

	printf("\twatek glowny: wyslanie sygnalu zabicia watku odlaczonego\n");
	pthread_cancel(tid);

	//Czy watek zostal zabity? Jak to sprawdzic?
    // Jesli watek zostal zakonczony nie mozemy sprawdzic czy zabijanie zakonczylo sie sukcesem 
    printf("\twatek glowny: Sprawdzenie czy watek odlaczony zostal zabity: \n");
	printf("\twatek glowny: sprawdzanie wartosci zmiennej wspolnej\n");
    for (i = 0; i < 5; i++){
		sleep(1);
		if (zmienna_wspolna != 0) break;
	}
    if (zmienna_wspolna == 0)
		printf("\twatek glowny: odlaczony watek ZABITY (ZNIKNELY ZASOBY) \n");

	//Watek odlaczony
	
	//Inicjacja atrybutow?
    pthread_attr_init(&attr);

	//Ustawianie typu watku na odlaczony
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	printf("watek glowny: tworzenie odlaczonego watku potomnego nr 3\n");
	pthread_create(&tid, &attr, zadanie_watku, NULL); //3 watek 

	//Niszczenie atrybutow
    pthread_attr_destroy(&attr);

	printf("\twatek glowny: koniec pracy, watek odlaczony pracuje dalej\n");
    //a phtread_exit(NULL) zakancza watek z wartoscia null
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
    //->exit(0) zakonczy cały program, co moze spowodowac ze odlaczone watki nie zdaza zakonczyc pracy
}

