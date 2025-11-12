#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void main() {
     pid_t f1 = fork();
     if (f1 == 0) {
        printf("f1 is done \n");
        exit(5);
     }
    pid_t f2 = fork();
     if (f2 == 0) {
          printf("f2 is done \n");
        exit(10);
        
     }
    pid_t f3 = fork();
     if (f3 == 0) {
          printf("f3 is done \n");
        exit(3);
     }

     int value =0;
     int status;
     int fils[3];
     int tmp =0;
     
    while (tmp != -1) {
          tmp = wait(&status);
        if (tmp == f1) {
            fils[0] =   WEXITSTATUS(status);
        } else if (tmp == f2) {
         fils[1] =   WEXITSTATUS(status);
        } else {
             fils[2] =   WEXITSTATUS(status);
        }
    }

        
        value = fils[0]*fils[1] + fils[2];
        printf("la valeur est : %d : ", value);

}