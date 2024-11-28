#include<stdio.h>
#include<pthread.h>
#include<math.h>

//#define N 1000// liczba iteracji (elementów przetwarzanej tablicy): N – jako parametr
#define ROZMIAR 1000
#define LICZBA_W_MAX 2 //max liczba watkow
pthread_mutex_t muteks;
pthread_t watki[LICZBA_W_MAX];
double suma=0;

double funkcja ( double x );

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global=0;

static double calka_global=0.0;
static double a_global;
static double b_global;
static double dx_global;
static int N_global;

void* calka_fragment_petli_w(void* arg_wsk);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w){
  
  int p;
  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;

  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  //printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);


  // tworzenie struktur danych do obsługi wielowątkowości
  int i; int indeksy[LICZBA_W_MAX];
 // printf("Podaj liczbe watkow: "); scanf("%d",&p);


  // tworzenie wątków
  for(i=0;i<p;i++) indeksy[i]=i;

  pthread_mutex_init( &muteks, NULL);
  for(i=0; i<LICZBA_W_MAX; i++ ) pthread_create( &watki[i], NULL, calka_fragment_petli_w, (void *) &indeksy[i] );

  // oczekiwanie na zakończenie pracy wątków
  for(i=0; i<LICZBA_W_MAX; i++ ) pthread_join( watki[i], NULL );
  printf("suma = %f\n",calka_global); 


  return(calka_global);
}

void* calka_fragment_petli_w(void* arg_wsk){

  int my_id=*((int*)arg_wsk); //od 0 do p-1

  double a, b, dx; // skąd pobrać dane a, b, dx, N, l_w ? 
  int N, l_w;      // wariant 1 - globalne

  // a = a_global; // itd. itp. - wartości globalne nadaje calka_zrownoleglenie_petli

  // dekompozycja cykliczna
  // int my_start = 0;
  // int my_end = 0;
  // int my_stride = 0;

  // dekompozycja blokowa
  int el_na_watek=ceil((float)ROZMIAR/LICZBA_W_MAX);
  int my_start = el_na_watek*my_id;
  int my_end = el_na_watek*(my_id+1);
  if(my_end>N) my_end=N;
  int my_stride = 1;

 


  // something else ? (dekompozycja blokowo-cykliczna)

  printf("\nWątek %d: my_start %d, my_end %d, my_stride %d\n", 
	 my_id, my_start, my_end, my_stride);


  int i;
  double calka = 0.0;
  
  for(int i=my_start;i<my_end;i+=my_stride){
    double x1 = a + i*dx;
    calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
  }

  pthread_mutex_lock( &muteks );
  calka_global += calka;
  pthread_mutex_unlock( &muteks );
  
    
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);

  }



