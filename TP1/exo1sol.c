#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int choix;
    char fichier[100];

    printf("=== Menu ===\n");
    printf("1. Créer un fichier (touch)\n");
    printf("2. Afficher un fichier (cat)\n");
    printf("3. Supprimer un fichier (rm)\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    printf("Nom du fichier : ");
    scanf("%s", fichier);

    switch (choix) {
        case 1:
            // first => path to the executable
                // you may put in the first /bin/touch 
                // which is equivalent to touch
            // second => name of the command
            // third => arguments of the command
            // last => NULL to mark the end of the arguments
            execlp("touch", "touch", fichier, NULL);
            break;
        case 2:
            execlp("cat", "cat", fichier, NULL);
            break;
        case 3:
            execlp("rm", "rm", fichier, NULL);
            break;
        default:
            printf("Choix invalide.\n");
            exit(1);
    }

    // Si execlp échoue
    perror("execlp");
    return 1;
}