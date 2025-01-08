#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // standardy C99 i C11 nie wymagajÄ definiowania staĹej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char** argv){ // program obliczania przybliĹźenia PI za pomocÄ wzoru Leibniza
                  // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
  
  //zmiany:
  int rank,ranksent,size,source,dest,tag;
  int i;
  const int root=0;
  MPI_Status status;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int max_liczba_wyrazow=0;
  double pi_approx=0;
  double result=0;


  //MPI

  if(size>1){

    if(rank==root){
        printf("Thread count is %d\n", size);
        printf("Podaj maksymalna liczbe wyrazow do obliczenia przyblizenia PI\n");
        scanf("%d", &max_liczba_wyrazow);
    }
    printf("Rank: %d is calling broad cast\n",rank);

//broadcast 
    MPI_Bcast(&max_liczba_wyrazow,1,MPI_INT,root,MPI_COMM_WORLD);

    int start=ceil((float)max_liczba_wyrazow/size)*rank;
    int end=ceil((float)max_liczba_wyrazow/size)*(rank+1);

    if(end>max_liczba_wyrazow){
        end=max_liczba_wyrazow;
    }
    
    int step=1;
    printf("My rank is %d, start at %d, end at %d, step by %d\n", rank, start, end, step);
     SCALAR suma_plus=0.0;
    SCALAR suma_minus=0.0;
    
    for(i=start; i<end; i+=step){  
    int j = 1 + 4*i; 
    suma_plus += 1.0/j;
    suma_minus += 1.0/(j+2.0);
    //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
    //  	 4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));
  }
  pi_approx = 4*(suma_plus-suma_minus);
  printf("Rank %d: my approximate pi is: %f\n", rank, pi_approx);


  //reduce
    MPI_Reduce(&pi_approx,&result,1,MPI_DOUBLE,MPI_SUM,root,MPI_COMM_WORLD);
    if(rank==root){
        printf("Rank %d: final result (after sum) is %f\n", rank, result);
    }
    else{
         printf("Podaj maksymalna liczbe wyrazow do obliczenia przyblizenia PI\n");
    scanf("%d", &max_liczba_wyrazow);
    //  double t = MPI_Wtime();
	printf("Pojedynczy proces o randze: %d\n", rank);
     // wzĂłr: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.  
    SCALAR suma_plus=0.0;
    SCALAR suma_minus=0.0;
    int i=0;
    for(i=0; i<max_liczba_wyrazow; i++)
    {  
        int j = 1 + 4*i; 
        suma_plus += 1.0/j;
        suma_minus += 1.0/(j+2.0);
        //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
        //4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));
    }
    pi_approx = 4*(suma_plus-suma_minus);
     //  t = MPI_Wtime() - t;
    printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
    }


    
  }

 
  MPI_Finalize();
  return (0);
  
}

