#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    double a;
    double b;
    double c;
}struktura;

void *funkcja_watku(void *arg){
    struktura s_lok=*((struktura *)arg); //kopiowanie wartosci(struktura lokalna)
    double sum=0;
    s_lok.a++;
    s_lok.b++;
    s_lok.c++;

    sum=s_lok.a+ s_lok.b+s_lok.c;
  
    //dostep do zmiennych lokalnych
    printf("\nWatek: s_lok.a = %lf, s_lok.b=%lf s_lok.c=%lf suma=%lf",s_lok.a, s_lok.b,s_lok.c,sum);
    //dostep do zmiennych nielokalnych- kopiowanie wskaźnika z rzutowaniem typu
    struktura *s_wsk=(struktura *) arg;
    printf("zewn: s_zewn.a=%lf, s_zewn.b =%lf s_zewn.c=%lf \n",s_wsk->a,s_wsk->b,s_wsk->c);
}

int main(){
    struktura s;
    s.a=1;
    s.b=4.5;
    s.c=6.0;
    int liczba_watkow=10;
    pthread_t watki[liczba_watkow];
    int watki_id[liczba_watkow];

   

    for(int i = 0; i < liczba_watkow; i++){
        pthread_create(&watki[i],NULL,funkcja_watku,(void*) &s);
    }

   //czekanie na zakonczenie wszystkich watkow
    for (int i = 0; i < liczba_watkow; i++) {
        pthread_join(watki[i], NULL);
    }

   printf("Zakonczenie dzialania wszystkich watkow.\n");
    return 0;

}