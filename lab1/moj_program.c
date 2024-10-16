#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "pomiar_czasu.h"
 
const int liczba = 100000;

void main(){

  double a, b, c;
  int i,j,k,l;
  double t1=0;
  double t2=0;
  t1=czas_zegara();
  t2=czas_CPU();

  k = -50000;
  //poczatek
  for(i=0;i<liczba;i++){

    printf("%d ",k+i);

  }
  
  printf("\n");
  //koniec
	
  t1=czas_zegara()-t1;
  t2=czas_CPU()-t2;
  printf("Czas wykonania %d operacji wejscia/wyjscia zegarowy: %f \n",liczba,t1);
  printf("Czas wykonania %d operacji wejscia/wyjscia  CPU: \%f \n",liczba,t2);

  t1=czas_zegara();
  t2=czas_CPU();
  a = 1.000001;
  //poczatek
  for(i=0;i<liczba;i++){

    a = 1.000001*a+0.000001; 

  }
  //koniec
  t1=czas_zegara()-t1;
  t2=czas_CPU()-t2;

  printf("Wynik operacji arytmetycznych: %lf\n", a);
  printf("Czas wykonania %d operacji arytmetycznych zegar: %lf \n",liczba,t1);
  printf("Czas wykonania %d operacji arytmetycznych CPU: %lf \n",liczba,t2);
  


}
