#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t child_pid;

//to switch the order we switch the two conditions of the if statments
// the parent become i%2 ==1 and child i%2==0

void handler(int sig){
}

int main(){
    signal(SIGUSR1, handler);
    
    child_pid = fork();
    int start = 97;

    if(child_pid==0){
        for(int i=0;i<26;i++){
            printf("%c", start+i);
            fflush(stdout);
            if(i%2 == 1){
                kill(getppid(), SIGUSR1);
                pause();
            }
        }
        kill(getppid(), SIGUSR1);
        exit(0);
        
    }else{
        for(int i=0;i<26;i++){
            if(i%2 == 0){
                kill(child_pid, SIGUSR1);
                pause();
            }
            
            printf("%c", start+i-32);
            fflush(stdout);
        }
        kill(child_pid, SIGUSR1);
        printf("\n");
        wait(NULL);
    }
    
    return 0;
}