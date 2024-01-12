#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#define N_THREADS 10

pthread_mutex_t a_lock = PTHREAD_MUTEX_INITIALIZER; 
int total=0;

void error(char str[]){
    fprintf(stderr, "\033[31mError: %s.\033[m", str);
    exit(1);
}

void* sum(void* param){
    pthread_mutex_lock(&a_lock);
    total += 1;
    printf("thread added up to %d\n", total);
    pthread_mutex_unlock(&a_lock);
    return 0;
}

int main(){
    pthread_t threads[N_THREADS];
    int i;

    for(i=0; i < N_THREADS; i++){
        if(pthread_create(&threads[i], NULL, sum, NULL) == -1){
            error("Could not create thread");
        }
    }

    void* results;

    for(i=0; i < N_THREADS; i++){
        if(pthread_join(threads[i], &results) == -1){
            error("Could not close thread");
        }
    }

    printf("\nSum: %d", total);
    return 0;
}