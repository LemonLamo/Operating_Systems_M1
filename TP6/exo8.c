#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>


void main(){
    int pipes[2];
    pipe(pipes);
    pid_t child1 = fork();
    if(child1 == 0){
        close(pipes[1]);
        char buffer[100];
        while(1){
            read(pipes[0], buffer, 1);
            printf("%s", buffer);
            fflush(stdout);
        }
        exit(0);
    }else{
        close(pipes[0]);
        char out;
        while(1){
            scanf("%c", &out);
            write(pipes[1], &out, 1);
        }
        close(pipes[1]);
        wait(NULL);
        printf("Child process finished\n");
    }

}