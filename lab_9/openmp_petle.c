#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];
  int i,j;

    //inicjalizowanie tablicy [] []
  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwojna petla - sekwencyjnie - suma
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
 printf("Suma wyrazow tablicy sekwencyjnie: %lf\n", suma);

  //omp_set_nested(1);//ustawienie opcji dla zagniezdzonych petli, zagniezdzenie rownolegle , 0 to domyslna wartosc


  //dekompozycja wierszowa
  // double suma_wierszowa = 0.0;
  // #pragma omp parallel for default(none) shared(a) schedule (static,2)  reduction(+:suma_wierszowa) ordered
  // for (int i = 0; i < WYMIAR; i++) {
  //   for (int j = 0; j < WYMIAR; j++){
  //     suma_wierszowa += a[i][j];

  //     #pragma omp ordered
  //     printf("a [%1d,%1d] - W_%1d \n", i, j, omp_get_thread_num());
  //   }
  // }

  // printf("Suma wyrazow tablicy rownolegle (dekompozycja wierszowa): %lf\n\n", suma_wierszowa);

// // dekompozycja kolumnowa
//   omp_set_nested(1);
//   double suma_kolumnowa = 0.0;
//   #pragma omp parallel for default(none) shared(a)  schedule(dynamic) reduction(+:suma_kolumnowa) ordered
//   for (int j = 0; j < WYMIAR; j++) {
//     for (int i = 0; i < WYMIAR; i++){
//       suma_kolumnowa += a[i][j];

//       #pragma omp ordered
//       printf("a [%1d,%1d] - W_%1d \n", i, j, omp_get_thread_num());
//     }
//   }

//   printf("Suma wyrazow tablicy rownolegle (dekompozycja kolumnowa): %lf\n", suma_kolumnowa);

// dekompozycja kolumnowa
  omp_set_nested(1);
  double suma_parallel = 0;
 

  #pragma omp parallel default(none) shared(suma_parallel,a) 
  {
  double suma_tmp=0.0;

  #pragma omp for
   for (int j = 0; j < WYMIAR; j++) {
    for (int i = 0; i < WYMIAR; i++){
      suma_tmp += a[i][j];}}
  
  #pragma omp critical(suma_parallel)
      suma_parallel += suma_tmp;
  
  #pragma omp barrier
        printf("Suma wyrazow bez reduction: %lf\n\n", suma_parallel);
  }
  


    return 0; 
}