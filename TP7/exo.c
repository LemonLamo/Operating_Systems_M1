#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
 
int base ,  n ;

void multiply () {
    n = base * n ;
    printf("child's result  : %d /n ", &n);

}


void main () {
   int  p , i ;
   printf ("enter your base number : /n");
   scanf("%d", &n );
   printf("enter your exponent : /n");
   scanf("%d", &p);
   
   phtread_t child[p];
   for (int i=0 , i<p , i++) {
      pthread_create(child[i], NULL ,multiply,NULL);
   }

}