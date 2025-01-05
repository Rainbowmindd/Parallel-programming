#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18

//Sposoby okreslenia liczy watkow
// 1.zmienna srodowiskowa
  //w terminalu: export OMP_NUM_THREADS=4
//2. klauzula num_threads w dyrektywe parallel, - tylko dla danej dyrektywy
  /*
    #pragma  omp parallel for num_threads(4) default(none) shared(a)
    for(int i = 0; i < WYMIAR; i++) a[i] = 1.02 * i;
  */

  // 3. funkcja omp_set_num_threads - dla wszystkich rownoleglych akcji
 

int main ()
{
  double a[WYMIAR];
  omp_set_num_threads(4);

#pragma omp  parallel for default(none) shared(a)
  for(int i=0;i<WYMIAR;i++) a[i]=1.02*i;

  // petla sekwencyjna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
      suma += a[i];
  }
  
  printf("Suma wyrazow tablicy: %lf\n", suma);

  // petla do modyfikacji - docelowo rownolegla w OpenMP

  double suma_parallel=0.0;

//zad3 - default(none) wymusza okreslenie jawnosci zmiennych
// #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel) ordered 
//zad5
//1- (static, 3)  iteracje w porcjach po 3, jesli liczba iteracji nie jest podzielna przez 3 to pozostale iteracje sa rozdzielane w kolejnosci
// #pragma omp parallel for default(none) shared(a) schedule (static, 3) reduction (+ : suma_parallel) ordered 

//2 (static)- domyslny rozmiar = wymiar/liczba_watkow 18/4= 4.5  0 i 1 po 5, 3 i 4 po 4 ,  iteracje w stalych porcjach, zawsze tak samo jest rozdzielane przy kazdym wywolaniu
// #pragma omp parallel for default(none) shared(a) schedule (static) reduction (+: suma_parallel) ordered 

//3 (dynamic, 2) - dynamicznie przydzielane iteracje po 2 dla kazdego, bardziej rownomierne obciazenie jesli rozna dlugosc kazdego z obliczen, inny czas
// #pragma omp parallel for default(none) shared(a) schedule(dynamic,2) reduction (+: suma_parallel) ordered

//4 (dynamic) domyslny rozmiar porcji 1, dynamicznie przydzielane iteracje, watek bierze jedna->konczy, bierze nastepna itp
#pragma omp parallel for default(none) shared(a) schedule (dynamic) reduction (+: suma_parallel) ordered

  for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
      suma_parallel += a[i];

//wymuszanie kolejnosci operacji    
#pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
  }

  printf("\nSuma wyrazow tablicy rownolegle (z klauzula - ORDERED: %lf\n",
	 suma_parallel);

}