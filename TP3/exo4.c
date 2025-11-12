#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t filspid;

void terminerfils(){
   kill(filspid, SIGKILL);
}

void main(){
    filspid = fork();
    if(filspid==0){
        while(1){}
        exit(0);
    }
    alarm(10);
    signal(SIGALRM, terminerfils);
    wait(NULL);
    printf("le fils a été terminé\n");
    exit(0);
}