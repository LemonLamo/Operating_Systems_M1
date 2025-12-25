# Primitives de manipulation des processus en C (Systèmes d’exploitation)


## 1. Cycle de vie d’un processus

Un **processus** est une instance d’un programme en cours d’exécution.

### États principaux
- **Création** : `fork()`
- **Exécution** : instructions du programme
- **Attente** : `wait()`, `waitpid()`
- **Fin** : `exit()`

---

## 2. fork()

### Rôle
Crée un **nouveau processus** (processus fils) par duplication du processus courant (père).

### Prototype
```c
#include <unistd.h>

pid_t fork(void);
Valeur de retour
Valeur	Signification
> 0	PID du fils (dans le père)
0	Processus fils
-1	Erreur

Exemple fondamental
c
Copy code
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Je suis le fils\n");
    } else if (pid > 0) {
        printf("Je suis le père\n");
    } else {
        perror("fork");
    }

    return 0;
}
Points d’examen importants
Le code après fork() est exécuté deux fois

Le fils a une copie de l’espace mémoire du père

L’ordre d’exécution n’est pas déterministe

3. execlp()
Rôle
Remplace complètement le programme courant par un nouveau programme.

⚠️ Si execlp() réussit, le code après n’est jamais exécuté

Prototype
c
Copy code
#include <unistd.h>

int execlp(const char *file, const char *arg0, ..., NULL);
Exemple
c
Copy code
#include <stdio.h>
#include <unistd.h>

int main() {
    execlp("ls", "ls", "-l", NULL);
    perror("execlp"); // exécuté seulement si erreur
    return 1;
}
Utilisation classique avec fork
c
Copy code
pid_t pid = fork();

if (pid == 0) {
    execlp("ls", "ls", NULL);
    perror("execlp");
    exit(1);
}
4. exit()
Rôle
Termine le processus et retourne un code de sortie au père.

c
Copy code
#include <stdlib.h>

void exit(int status);
Convention
0 → succès

!= 0 → erreur

Exemple
c
Copy code
exit(0);
exit(1);
5. wait()
Rôle
Bloque le processus père jusqu’à la fin d’un processus fils.

Prototype
c
Copy code
#include <sys/wait.h>

pid_t wait(int *status);
Variable status
Permet d’analyser la fin du fils.

Macros essentielles
c
Copy code
WIFEXITED(status)      // vrai si fin normale
WEXITSTATUS(status)   // code retourné par exit()
Exemple
c
Copy code
int status;
wait(&status);

if (WIFEXITED(status)) {
    printf("Code de sortie = %d\n", WEXITSTATUS(status));
}
6. waitpid()
Rôle
Version avancée de wait(), permet d’attendre :

un fils précis

ou sans blocage

Prototype
c
Copy code
pid_t waitpid(pid_t pid, int *status, int options);
Paramètre pid
Valeur	Effet
> 0	attendre ce PID précis
-1	équivalent à wait()

Option importante
c
Copy code
WNOHANG   // non bloquant
Exemple
c
Copy code
waitpid(pid, &status, 0);
7. sleep()
Rôle
Suspend l’exécution du processus pendant N secondes.

Prototype
c
Copy code
#include <unistd.h>

unsigned int sleep(unsigned int seconds);
Exemple
c
Copy code
sleep(2);
8. Exemple complet (fork + execlp + wait)
c
Copy code
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    } else {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Fils terminé avec code %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
9. Compilation et exécution d’un programme C
Étape 1 : Compilation
bash
Copy code
gcc programme.c -o programme
Étape 2 : Exécution
bash
Copy code
./programme
Compilation avec warnings (recommandé examen)
bash
Copy code
gcc -Wall -Wextra programme.c -o programme
10. Erreurs fréquentes à l’examen
Oublier NULL dans execlp

Ne pas tester le retour de fork

Mettre du code après execlp sans perror

Oublier wait() → processus zombie

Confondre PID père / fils

11. Schéma mental à retenir
scss
Copy code
fork()
 ├─ père → wait()
 └─ fils → execlp() → exit()





