#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


int N =10000;
int *A, *B, *C;

typedef struct {
    int debut_ligne;
    int fin_ligne;
    int debut_c;
    int fin_c;
} donnee;



void *add_matrix_top_left(void *arg) {
    donnee *data = (donnee *)arg;

    for (int i = data->debut_ligne; i < data->fin_ligne; i++) {
        for (int j = data->debut_c; j < data->fin_c; j++) {
            C[i*N + j] = A[i*N + j] + B[i*N + j];
        }
    }
    return NULL;
}

void *add_matrix_top_right(void *arg) {
    donnee *data = (donnee *)arg;

    for (int i = data->debut_ligne; i < data->fin_ligne; i++) {
        for (int j = data->debut_c; j < data->fin_c; j++) {
            C[i*N + j] = A[i*N + j] + B[i*N + j];
        }
    }
    return NULL;
}

void *add_matrix_bottom_left(void *arg) {
    donnee *data = (donnee *)arg;

    for (int i = data->debut_ligne; i < data->fin_ligne; i++) {
        for (int j = data->debut_c; j < data->fin_c; j++) {
            C[i*N + j] = A[i*N + j] + B[i*N + j];
        }
    }
    return NULL;
}

void *add_matrix_bottom_right(void *arg) {
    donnee *data = (donnee *)arg;

    for (int i = data->debut_ligne; i < data->fin_ligne; i++) {
        for (int j = data->debut_c; j < data->fin_c; j++) {
            C[i*N + j] = A[i*N + j] + B[i*N + j];
        }
    }
    return NULL;
}



int main() {
    pthread_t t1, t2, t3, t4;

    
    A = malloc(N*N* sizeof(int));
    B = malloc(N*N* sizeof(int));
    C = malloc(N*N* sizeof(int));

   
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i*N + j] = 1;
            B[i*N + j] = i*N + j;
        }
    }

    int mid = N / 2;

    donnee d1 = {0, mid, 0, mid};      
    donnee d2 = {0, mid, mid, N};    
    donnee d3 = {mid, N, 0, mid};     
    donnee d4 = {mid, N, mid, N};     

   
    pthread_create(&t1, NULL, add_matrix_top_left, &d1);
    pthread_create(&t2, NULL, add_matrix_top_right, &d2);
    pthread_create(&t3, NULL, add_matrix_bottom_left, &d3);
    pthread_create(&t4, NULL, add_matrix_bottom_right, &d4);

   
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);


    return 0;
}
