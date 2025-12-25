#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait
 
int cpt = 0;
pid_t pid;
 
int main(){
    // ===== Création des 5 fils =====
    while ((cpt < 5) && (pid=fork())){
        cpt++;
    }
    // ===== Code des fils =====
    if(!pid){
        printf("Fils %d de père %d\n", getpid(), getppid());
    } 
    // ===== Code du père =====
    else{          
        while(wait (NULL) != -1);   // ==> while(waitpid(-1, NULL, 0) != -1);
        printf("Père : Fin de tous les fils créés\n");
    }
    return 0;
}