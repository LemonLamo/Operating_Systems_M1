#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void main () {
     int status , i , j ;

     for (int i=0 , i<5 , i++) {
         pid_t f = fork();
      if (f == 0) {
          printf(" je suis le fils numero:%d \nmon pid est : %d \net de mon pere est : %d \n ", i, getpid(), getppid()); 
          printf("execution terminé \n");
          exit(i);
      };
     }
  
   
 
}