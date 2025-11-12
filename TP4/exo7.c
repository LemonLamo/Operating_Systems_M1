#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

    pid_t fils1 , fils2;
    int counter=1;


    void counterfils() {
           counter++; 
           printf("le compteur de %d : %d \n",getpid(), counter );
           fflush(stdout);
           kill(getppid(), SIGCONT);

    }
       void counterfils2() {
           counter=counter*2; 
           printf("le compteur de %d : %d \n",getpid(), counter );
           fflush(stdout);
           kill(getppid(), SIGCONT);

    }

    void counterparent() {
         counter++;
          printf("le compteur de %d : %d \n", getpid(), counter );
          fflush(stdout);
          if (counter >5) {
            //when you do a kill(id of the process you gonna send to, signal code)
            //but signal()
            kill(fils1,SIGTERM);
            kill(fils2,SIGTERM);
            exit(0);
          }
          if (counter%2==0) {
            kill(fils1, SIGUSR1);
          } else {
               kill(fils2, SIGUSR2);
          }
        
    }

int main() {  
    
  

     fils1 = fork();
     //fork either returns a pid or 0 , if you are in parent it will return the pid of the child 
     //if you are the child it will return 0
        if (fils1 == 0) {
            printf("je suis le fils %d et j'ai ete crée par %d \n", getpid(), getppid());
            signal(SIGUSR1, counterfils);
            while(1) {
            }
            exit(0);
        }
      fils2= fork();
     if (fils2 == 0) {
          printf("je suis le fils %d et j'ai ete crée par %d \n", getpid(), getppid());
          signal(SIGUSR2, counterfils2);
        while(1) { 
            }
            exit(0);
     }

    printf("je suis le parent %d et j'ai crée les fils %d et %d \n", getpid(), fils1, fils2);  
        signal(SIGCONT, counterparent);
        sleep(5);
        kill(fils1, SIGUSR1);
        while(1) {

        }

    return 0;
}