#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


int buffer_size =5;

sem_t empty;
sem_t full;
int indexprod;
int indexcons;
int buffer[buffer_size];
pthread_mutex_t mutex;

int prduce() {
    return rand();
}
int consume(int item) {
    printf("consumer got %d /n", item);
}  

void producer() {
    int item;
  
     while (1){
        sem_wait(&empty);
        item = prduce();
        pthread_mutex_lock(&mutex);
        //producing
        buffer[indexprod] = item;
        printf("producer made %d /n", item);
        indexprod = (indexprod +1) % buffer_size;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
     }
}

void consumer() {
    int item;
    while(1) {
      sem_wait(&full);
      pthread_mutex_lock(&mutex);
        //consuming
        item = buffer[indexcons];
        
        indexcons = (indexcons +1) % buffer_size;
      pthread_mutex_unlock(&mutex);
        consume(item);
        sem_post(&empty);

    }
}

void main () {
    pthread_t prod , cons;
    sem_init(&empty,0,buffer_size);
     sem_init(&full,0,0);

     pthread_create(&prod,NULL, producer,NULL);
     pthread_create(&cons,NULL,consumer,NULL);

     pthread_join(&prod,NULL);
     pthread_join(&cons,NULL);


}