#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

void main(){
    int pipechild1[2];
    int pipechild2[2];
    int childparentpipe1[2];
    int childparentpipe2[2];
    pipe(pipechild1);
    pipe(pipechild2);
    pipe(childparentpipe1);
    pipe(childparentpipe2);
    pid_t child1 = fork();
    if(child1 == 0){
        close(pipechild2[0]);close(pipechild2[1]);
        close(childparentpipe2[0]);close(childparentpipe2[1]);

        close(pipechild1[1]);
        close(childparentpipe1[0]);
        int input;
        int total = 0;
        while(read(pipechild1[0], &input, sizeof(input))){
            total += input;
        }
        close(pipechild1[0]);
        write(childparentpipe1[1], &total, sizeof(total));
        close(childparentpipe1[1]);
        exit(0);
    }
    pid_t child2 = fork();
    if(child2 == 0){
        close(pipechild1[1]);close(pipechild1[0]);
        close(childparentpipe1[0]);close(childparentpipe1[1]);

        close(childparentpipe2[0]);
        close(pipechild2[1]);

        int times[26] = {0};
        char buffer;
        while(read(pipechild2[0], &buffer, 1)){
            buffer = toupper(buffer);
            times[buffer - 'A']++;
        }
        close(pipechild2[0]);
        for(int i = 0; i < 26; i++){
            write(childparentpipe2[1], &times[i], sizeof(times[i]));
        }
        close(childparentpipe2[1]);
        exit(0);
    }

    close(pipechild1[0]);
    close(pipechild2[0]);
    close(childparentpipe1[1]);
    close(childparentpipe2[1]);
    char out[100];
    scanf("%s", out);
    for(int i = 0; i < 20; i++){
        if(out[i] >='a' && out[i] <='z' || out[i] >='A' && out[i] <='Z'){
            char c = out[i];
            write(pipechild2[1], &c, sizeof(c));
        }
        if (out[i] >= '0' && out[i] <= '9'){
            int number = out[i] - '0';
            write(pipechild1[1], &number, sizeof(number));
        }
        if(out[i] == '\0') {
            break;
        }
    }
    close(pipechild1[1]);
    close(pipechild2[1]);
    int sum;
    read(childparentpipe1[0], &sum, sizeof(sum));
    printf("la somme des chiffres: %d\n", sum);
    int times[26];
    for(int i = 0; i < 26; i++){
        read(childparentpipe2[0], &times[i], sizeof(times[i]));
    }
    close(childparentpipe2[0]);

    printf("la frequence des lettres:\n");
    for(int i = 0; i < 26; i++){
        if(times[i] > 0){
            printf("%c: %d\n", 'A' + i, times[i]);
        }
    }
    close(childparentpipe2[0]);
    wait(NULL);
}