#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
 
char c; 
pthread_mutex_t lock;

void* write(void* arg) {
    while(1) {
       pthread_mutex_lock(&lock);
    printf("%c", c);
    if(c == 'F') break;
    }
    pthread_exit(NULL);
}

void* read(void* arg) {
    while(1) {
         getchar(&c);
    pthread_mutex_unlock(&lock);
        if(c == 'F') break;
    }
   pthread_exit(NULL);
}


void main () {
    
    pthread_t child[2];

    pthread_mutexattr_t atr = PTHREAD_MUTEX_PRIVATE;
    pthread_mutexattr_init(&atr);
    pthread_mutex_init(&lock , &atr);
   
    pthread_create(&child[0], NULL ,&read,NULL);
    pthread_create(&child[1], NULL ,&write,NULL);

    pthread_join(child[0],NULL );
    pthread_join(child[1],NULL );


}