#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void error(char str[]){
    fprintf(stderr, "\033[31mError: %s.\033[m\n", str);
    exit(1);
}

int main(){
    pid_t pid;

    pid = fork();

    if(pid == -1) error("Can't fork");

    if(!pid){
        printf("Process %d: I'm the son\n", pid);
    }
    else{
        printf("Process %d: I'm the father\n", pid);
    }
}
