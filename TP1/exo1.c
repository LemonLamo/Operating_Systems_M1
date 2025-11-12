#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//execlp pour executer la commande ls 
void main() {
    execlp("bin/ls","ls","-l");
    
}
