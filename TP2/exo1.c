#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void main () {
      pid_t fils1 = fork();
      if (fils1 == 0) {
          printf("mon pid est : %d \net de mon pere est : %d \n ", getpid(), getppid()); 
          sleep(5);
          printf("execution terminé \n");
          exit(0);
      };

        pid_t fils2 = fork();
      if (fils2 == 0) {
          printf("mon pid est: %d \net du pere :%d \n ", getpid(), getppid()); 
          sleep(5);
           printf("execution terminé \n");
            exit(0);
      }; 
      int status;
      wait(&status);
      printf("le pere a terminé son execution");

}