#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, sleep
#include <sys/wait.h>   // wait

int main() {
    int cpt = 0, etat;
    pid_t pid, pidw;

    // ===== Création des 5 fils =====
    while ((cpt < 5) && (pid = fork())) {
        cpt++;
    }

    // ===== Code des fils =====
    if (pid == 0) {
        printf("Fils %d (ordre %d) de père %d\n", getpid(), cpt + 1, getppid());
        sleep(10);                
        exit(cpt + 1);            
    }

    // ===== Code du père =====
    else {
        // Le père attend la fin de tous les fils
        while ((pidw = wait(&etat)) != -1) {
            if (WIFEXITED(etat)) {
                printf("Père : fils %d terminé (ordre de création = %d)\n",
                       pidw, WEXITSTATUS(etat));
            }
        }
        printf("Père : fin de tous les fils.\n");
    }

    return 0;
}