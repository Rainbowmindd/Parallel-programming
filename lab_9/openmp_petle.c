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

  omp_set_nested(1);//ustawienie opcji dla zagniezdzonych petli


  //dekompozycja wierszowa
  double suma_wierszowa = 0.0;
  #pragma omp parallel for default(none) shared(a) private(i,j) schedule (static,2)  reduction(+:suma_wierszowa) ordered
  for (int i = 0; i < WYMIAR; i++) {
    for (int j = 0; j < WYMIAR; j++){
      suma_wierszowa += a[i][j];

      #pragma omp ordered
      printf("a [%1d,%1d] - W_%1d \n", i, j, omp_get_thread_num());
    }
  }

  printf("Suma wyrazow tablicy rownolegle (dekompozycja wierszowa): %lf\n\n", suma_wierszowa);

// dekompozycja kolumnowa
  omp_set_nested(1);
  double suma_kolumnowa = 0.0;
  #pragma omp parallel for default(none) shared(a,i) private(j) schedule(dynamic) reduction(+:suma_kolumnowa) ordered
  for (int j = 0; j < WYMIAR; j++) {
    for (int i = 0; i < WYMIAR; i++){
      suma_kolumnowa += a[i][j];

      #pragma omp ordered
      printf("a [%1d,%1d] - W_%1d \n", i, j, omp_get_thread_num());
    }
  }

  printf("Suma wyrazow tablicy rownolegle (dekompozycja kolumnowa): %lf\n", suma_kolumnowa);

  // podwojna petla - docelowo rownolegle
//   double suma_parallel=0.0; int i,j;
//   // ...
//   for(i=0;i<WYMIAR;i++) {
//     int id_w = omp_get_thread_num();
//     // #pragma omp ordered
//     // ...
//     for(j=0;j<WYMIAR;j++) {
//       suma_parallel += a[i][j];
//       // #pragma omp ordered
//       // dla dekompozycji 1D
//       //printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
//       // dla dekompozycji 2D
//       //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
//     }
//     // #pragma omp ordered
//     printf("\n");
//   }

//   printf("Suma wyrazow tablicy rownolegle: %lf\n", suma_parallel);
    return 0; 
}