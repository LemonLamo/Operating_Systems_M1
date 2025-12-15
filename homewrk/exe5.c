#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void handler(int signum){
    printf("child process over capacity\n");
}

int cap = 100;

void main(){
    int pipes[2];
    pipe(pipes);
    pid_t child1 = fork();
    if(child1 == 0){
        close(pipes[1]);
        int buffer;
        int total = 0;
        while(read(pipes[0], &buffer, sizeof(buffer))){
            total += buffer;
            if(total > cap){
                kill(getppid(), SIGUSR1);
            }
        }
        close(pipes[0]);
        exit(0);
    }
    signal(SIGUSR1, handler);
    close(pipes[0]);
    int number;
    int done = 1;
    while(done){
        scanf("%d", &number);
        write(pipes[1], &number, sizeof(number));
        if(number == -1) {
            done = 0;
        }
    }
    close(pipes[1]);
    wait(NULL);
}