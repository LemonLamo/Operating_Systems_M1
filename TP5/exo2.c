#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


void main() {

    int pipes[2];
    pipe(pipes);
    pid_t filspid = fork();
    if(filspid==0){
        //child process
        close(pipes[1]); //close write end
        char c;
        while(read(pipes[0], &c, 1) > 0){
            putchar(c);
            fflush(stdout);
        }
        close(pipes[0]);
        exit(0);
    } else {
        //parent process
        close(pipes[0]); //close read end
        const char *message = "hello little one\n";
       
        write(pipes[1], message, 17);

        
        close(pipes[1]);
        wait(NULL); //wait for child to finish
        exit(0);
    }

}