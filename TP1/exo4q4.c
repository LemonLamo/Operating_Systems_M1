#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait

int cpt = 0;
int pid[5]; 
int i=0;
int pidw;

int main(){
    // ===== Création des 5 fils =====
    while ((cpt < 5) && (pid[i]=fork())){
        cpt++;
        i++;
    }
    // ===== Code des fils =====
    if(!pid[i]){
        printf("Fils %d de père %d\n", getpid(), getppid());
    } 
    // ===== Code du père =====
    else{          
        pidw = waitpid(pid[2], NULL, 0);
        printf("Père : Fin du dernier fils créé %d\n", pidw) ;
    }
    return 0;
}