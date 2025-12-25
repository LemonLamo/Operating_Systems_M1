#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    pid_t pid1, pid2, pid3;
    int status;
    int val1 = 0, val2 = 0, val3 = 0;

    // ===== Création du fils f1 =====
    pid1 = fork();
    if (pid1 == 0) {
        // Fils 1
        exit(5); // retourne 5
    }

    // ===== Création du fils f2 =====
    pid2 = fork();
    if (pid2 == 0) {
        // Fils 2
        exit(10); // retourne 10
    }

    // ===== Création du fils f3 =====
    pid3 = fork();
    if (pid3 == 0) {
        // Fils 3
        exit(3); // retourne 3
    }

    // ===== Processus père =====
    for (int i = 0; i < 3; i++) {
        pid_t terminated_pid = wait(&status);
        if (WIFEXITED(status)) {
            int val = WEXITSTATUS(status);
            printf("Le fils %d s'est terminé avec la valeur %d\n", terminated_pid, val);
            if (val == 5)
                val1 = val;
            else if (val == 10)
                val2 = val;
            else if (val == 3)
                val3 = val;
        }
    }

    int resultat = val1 * val2 + val3;
    printf("\nRésultat = %d * %d + %d = %d\n", val1, val2, val3, resultat);
    return 0;
}