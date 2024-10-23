#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna=0;

int main(int argc, char* argv[]){
  
  int pid, wynik, i;

  inicjuj_czas();
  
  for(i=0;i<1000;i++){
    
    pid = fork(); 	//tworzenie nowego procesu		
    
    if(pid==0){ 			
      
      zmienna_globalna++;

//wersja 1
      // char arg1[]="./zajecia2";
      // char arg2[]="Martyna";
      // char arg3[]="Kindrat";
      // char* arg[] = {arg1,arg2,arg3,NULL};
      // wynik=execv("./zajecia2",arg); 
//wersja 2
       char* arg[] = {"./zajecia2", argv[1], argv[2], NULL};
      wynik = execv("./zajecia2", arg);

      if(wynik==-1) 
         printf("Proces potomny nie wykonal programu\n"); 

      exit(0);
      
    } else {					
      
      wait(NULL);
      
    }
    
  }

  drukuj_czas();
  
}

  
