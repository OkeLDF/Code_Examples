#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N_THREADS 10

CRITICAL_SECTION lock;

int total=0;

void error(char str[]){
    fprintf(stderr, "\033[31mError: %s.\033[m", str);
    exit(1);
}

DWORD WINAPI sum(LPVOID Param){
    EnterCriticalSection(&lock);
    total += 1;
    LeaveCriticalSection(&lock);
    printf("Thread %6d added up to %d\n", GetCurrentThreadId(), total);
    return 0;
}
 
DWORD WINAPI print(LPVOID Param){
    printf("%s\n", Param);
    return 0;
}

int main(){
    DWORD threadId[N_THREADS];
    HANDLE threadHandle[N_THREADS];
    int i;

    InitializeCriticalSection(&lock);

    for(i=0; i < N_THREADS; i++){
        threadHandle[i] = CreateThread(NULL, 0, sum, NULL, 0, &(threadId[i]));
        if(!threadHandle[i]) error("Could not create thread");
    }
    
    for(i=0; i < N_THREADS; i++){
        WaitForSingleObject(threadHandle[i], INFINITE);
    }

    for(i=0; i < N_THREADS; i++){
        CloseHandle(threadHandle[i]);
    }

    DeleteCriticalSection(&lock);

    printf("\nSum: %d", total);
    return 0;
}