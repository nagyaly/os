#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>        //library for threads in C
/*
    thread routine must satisfy the following:
        1- return void pointer (void *)
        2- accept void pointer (void *)
    to compile the code, add -pthread
        gcc 3-1.c -o 3-1 -pthread
*/
void* my_routine(void* args){
    int i;
    for(i=0;i<5;i++){
        printf("Y: %d\n", i);
        sleep(1);
    }
    return NULL;
}
int main(){
    pthread_t tid;

    //create and start a thread
    // pthread_id, attributes, routine/function name, arguments
    pthread_create(&tid, NULL, my_routine, NULL);

    int i;
    for(i=0;i<5;i++){
        printf("x: %d\n", i);
        sleep(1);
    }

    //wait for the child thread
    pthread_exit(NULL);
    return 0;
}