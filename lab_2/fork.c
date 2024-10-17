#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna=0;

int main(){
  
  int pid, wynik, i;

  inicjuj_czas();
  
  for(i=0;i<1000;i++){
    
    pid = fork(); 	//tworzenie nowego procesu		
    
    if(pid==0){ 			
      
      zmienna_globalna++;

      char arg1[] = "./zajecia2";
      char arg2[] = "Martyna Kindrat";
      char* arg[] = {arg1,arg2,NULL};
      

       wynik=execv(arg[0],arg);  //uruchomienie zajecia2

      // char* arg[] = {"/bin/ls",".",NULL};
      // wynik=execv("./program",NULL);  //uruchomienie zajecia2.c
      if(wynik==-1) 
         printf("Proces potomny nie wykonal programu\n"); 

      exit(0);
      
    } else {					
      
      wait(NULL);
      
    }
    
  }

  drukuj_czas();
  
}

  
