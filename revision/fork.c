//explication de la primitive fork()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    pid_t pid;
    //creation d'un processus fils
    pid = fork();
    if (pid < 0) {
        //erreur lors de la creation du processus fils
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        //code du processus fils
        printf("Je suis le processus fils avec PID %d\n", getpid());
    } else {
        //code du processus pere
        printf("Je suis le processus pere avec PID %d et mon fils a pour PID %d\n", getpid(), pid);
    }
    return 0;
}