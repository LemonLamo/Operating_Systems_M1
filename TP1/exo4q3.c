#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait


int cpt = 0;
pid_t pid, pidw;

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
        pidw = waitpid(pid, NULL, 0);
        printf("Père : Fin du dernier fils créé %d\n", pidw) ;
    }
    return 0;
}