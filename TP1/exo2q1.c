#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait

int main(void){
	// ===== Création du fils =====
	int pid1=fork();

	if (pid1==0){
		printf("Bonjour :Je suis le fils , mon pid est %d et le pid de mon père est : %d   \n", getpid(), getppid()); 
		sleep(5);
	}
	else { // ===== Création du code du père =====
		sleep(2);
		printf("Je suis le pere - mon pid est %d et le pid de mon fils est : %d   \n", getpid(), pid1);
	}
	return 0;
}
