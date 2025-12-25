
#include <stdio.h>
#include <unistd.h>  // fork
#include <stdlib.h>  // exit

void main(){
  int pid = fork();
  if (pid==0){
    // ===== Code de fils 1 =====
    printf("fils1 de pid=%d: Bonjour\n", getpid());
    sleep(5);
    printf("fils1 de pid=%d: aurevoir\n", getpid());
    exit(1); 
    // ===== Fin du fils 1 =====
  }
  else { // ===== Suite du code du père =====
    int pid2= fork();
    if (pid2==0){
      // ===== Code de fils 2 =====
      printf("fils2 de pid=%d: Bonjour\n", getpid());
      sleep(5);
      printf("fils2 de pid=%d: aurevoir\n", getpid());
      exit(2); 
    }
    else{
      while(wait(NULL)!=-1);
      printf("les deux fils ont termine \n");
    }
  }
}






