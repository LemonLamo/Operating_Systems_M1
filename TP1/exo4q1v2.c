#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait

int cpt=0, etat, nb=0;
pid_t pid, pidw;

int main(){
    // ===== Création des 5 fils =====
    while ((cpt < 5) && (pid=fork())){
        cpt++;
    }
    // ===== Code des fils =====
    if(!pid){
        printf("Fils %d de père %d\n", getpid(), getppid());
        exit(cpt);
    } 

    // ===== Code du père =====
    else{                     
        while((nb < 3) && ((pidw=waitpid(-1, &etat, 0)) != -1)){
        if(WIFEXITED(etat)){

            int state = WEXITSTATUS(etat);

            if (state == 2)
                printf("Fin du fils %d avec code %d\n", pidw, state );
        }
            nb++;
        }
    }
    return 0;
}