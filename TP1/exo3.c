#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main() {
    pid_t fils = fork();
      if (fils == 0) {
          printf("le pid du fils est : %d, et du pere :%d", getpid(), getppid()); 
          sleep(5);
      } else {
        sleep(2);
        printf("le pid du fils %d est: %d", fils,getpid());
      }  
}