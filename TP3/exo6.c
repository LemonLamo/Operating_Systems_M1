#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int heures = 0;
    int minutes = 0;
    int secondes = 0;
    
    while (1) {
        printf("\033[H\033[J"); 
        printf("%02d:%02d:%02d\n", heures, minutes, secondes);
        fflush(stdout);
        sleep(1);
        secondes++;
        if (secondes == 60) {
            secondes = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            heures++;
        }
 
        if (heures == 24) {
            heures = 0;
        }
    }
    
    return 0;
}
