
# PARTIE I — SIGNAUX (Signals)

## 1. Qu’est-ce qu’un signal ?

Un **signal** est un **mécanisme asynchrone** utilisé par le noyau ou par un processus pour **notifier un autre processus qu’un événement s’est produit**.

➡ Contrairement aux appels système classiques, **un signal interrompt l’exécution normale du processus**.

---

## 2. Signaux les plus importants à connaître

| Signal | Signification |
|------|--------------|
| `SIGINT` | Interruption clavier (Ctrl+C) |
| `SIGTERM` | Demande de terminaison |
| `SIGKILL` | Terminaison immédiate (non interceptable) |
| `SIGSTOP` | Suspension du processus |
| `SIGCHLD` | Fin d’un processus fils |
| `SIGALRM` | Alarme (timer) |
| `SIGUSR1`, `SIGUSR2` | Signaux personnalisés |

---

## 3. Gestion des signaux : `signal()` vs `sigaction()`

### ❌ `signal()` (ancien, non fiable)
- comportement dépendant de l’implémentation
- **pas recommandé au niveau Master**

### ✅ `sigaction()` (standard POSIX)

#### Prototype
```c
#include <signal.h>

int sigaction(int signum,
              const struct sigaction *act,
              struct sigaction *oldact);
4. Handler de signal (fonction appelée à la réception)
Règles critiques
signature obligatoire :

c
Copy code
void handler(int signum);
ne jamais utiliser printf (non async-signal-safe)

préférer write() ou poser un flag global

5. Exemple : Intercepter SIGINT
c
Copy code
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    write(1, "SIGINT reçu\n", 12);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    while (1) {
        pause();
    }
}
6. Envoi de signaux
kill()
c
Copy code
kill(pid, SIGTERM);
raise() (au processus courant)
c
Copy code
raise(SIGINT);
7. SIGCHLD (important examen)
Signal envoyé au père quand un fils se termine.

Utilisé pour éviter les processus zombies.

c
Copy code
void handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}
PARTIE II — PIPES (IPC – Communication inter-processus)
1. Qu’est-ce qu’un pipe ?
Un pipe est un canal de communication unidirectionnel entre processus ayant un lien de parenté.

basé sur un buffer noyau

communication FIFO

communication par octets

2. Création d’un pipe
Prototype
c
Copy code
#include <unistd.h>

int pipe(int fd[2]);
fd	Rôle
fd[0]	lecture
fd[1]	écriture

3. Règles fondamentales (TRÈS IMPORTANT)
Toujours fermer les descripteurs inutilisés

Sinon : blocages ou deadlocks

Lecture bloquante si aucun écrivain

Écriture bloquante si buffer plein

4. Exemple : Communication père → fils
c
Copy code
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        close(fd[1]); // ferme écriture
        char buf[100];
        read(fd[0], buf, sizeof(buf));
        printf("Fils reçu : %s\n", buf);
    } else {
        close(fd[0]); // ferme lecture
        write(fd[1], "Bonjour", 7);
    }
}
5. Pipe + execlp (cas examen classique)
c
Copy code
pipe(fd);

if (fork() == 0) {
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    execlp("wc", "wc", "-l", NULL);
} else {
    close(fd[0]);
    write(fd[1], "hello\nworld\n", 12);
}
6. dup2()
Redirige un descripteur de fichier.

c
Copy code
dup2(fd[0], STDIN_FILENO);
➡ Base des pipelines shell (ls | wc -l)

PARTIE III — THREADS (pthread)
1. Processus vs Threads
Processus	Threads
Mémoire séparée	Mémoire partagée
Communication coûteuse	Communication directe
fork	pthread_create

2. Création d’un thread
Prototype
c
Copy code
#include <pthread.h>

int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
3. Fonction thread
c
Copy code
void* fonction(void* arg) {
    return NULL;
}
4. Exemple minimal
c
Copy code
#include <stdio.h>
#include <pthread.h>

void* f(void* arg) {
    printf("Thread exécuté\n");
    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, f, NULL);
    pthread_join(t, NULL);
    return 0;
}
5. pthread_join()
Bloque jusqu’à la fin du thread.

c
Copy code
pthread_join(thread, &retour);
6. Problème majeur : sections critiques
Les threads partagent la mémoire → conditions de course.

7. Mutex (synchronisation)
Déclaration
c
Copy code
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
Utilisation
c
Copy code
pthread_mutex_lock(&mutex);
// section critique
pthread_mutex_unlock(&mutex);
8. Exemple avec mutex
c
Copy code
int compteur = 0;
pthread_mutex_t mutex;

void* incr(void* arg) {
    pthread_mutex_lock(&mutex);
    compteur++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
9. Compilation avec pthread (TRÈS IMPORTANT)
bash
Copy code
gcc programme.c -o programme -pthread
⚠ Oublier -pthread = erreur à l’édition de liens

10. Comparaison examen
Sujet	Processus	Threads
fork	oui	non
Mémoire partagée	non	oui
IPC nécessaire	oui	non
Synchronisation	wait	mutex

11. Pièges classiques examen
Utiliser printf dans un handler de signal

Oublier de fermer un fd dans un pipe

Deadlock pipe (lecture bloquée)

Oublier pthread_join

Modifier une variable partagée sans mutex

Oublier -pthread à la compilation