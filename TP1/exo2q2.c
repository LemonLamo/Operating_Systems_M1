#include <stdio.h>
#include <unistd.h>  // fork
#include <stdlib.h>  // exit

void main(){
  int pid = fork();
  if (pid==0){
    // ===== Création du fils 1 =====
    printf("fils1 de pid=%d: Bonjour\n et le pid de mon père est : %d   \n", getpid(), getppid());
    sleep(5);
    printf("fils1 de pid=%d: aurevoir\n", getpid()); 
    exit(1); 
    // ===== Fin du fils =====
  }
  int pid2= fork();
  if (pid2==0){
    // ===== Création du fils 2 =====
    printf("fils2 de pid=%d: Bonjour\n et le pid de mon père est : %d   \n", getpid(), getppid());
    sleep(5);
    printf("fils2 de pid=%d: aurevoir\n", getpid());
    exit(2); 
  }
}