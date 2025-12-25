//les primitives du C pour la manipulation des processus
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>


int main() {
   //la primitive execlp() permet d'executer un programme
   //ici on execute la commande "ls -l /home"
    execlp("ls", "ls", "-l", "/home", NULL);
    //autre exemple 
    execlp("date", "date", NULL);
    //ou bien 
    execlp("/bin/ls","ls","-l","/usr",NULL); // ls -l /usr
   return 0;
   //explication de tout les arguments de execlp()
   /*
   1er argument : le nom du programme a executer (ici "ls")
   2eme argument : le nom de l'executable (par convention on met le meme nom que le 1er argument)
   3eme argument : les arguments du programme (ici "-l" et "/home")  
   dernier argument : NULL pour indiquer la fin des arguments
 
   Exercice : Ecrire un programme C qui utilise la primitive execlp() pour executer la commande "ping -c 4 google.com"
   et afficher le resultat dans un fichier "ping_result.txt".
  
  execlp("ping","ping","-c","4","google.com",">","ping_result.txt",NULL);
*/
}

