#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define NUM 10
void* my_routine(void* raw_args){
    char* c = (char*) raw_args;
    int i;
    for(i=0;i<4;i++){
        printf("%c: %d\n", *c, i);
        usleep(rand() % (1000 * 1000));     //fake random computation delay
    }
    return NULL;
}
int main(){
    srand(time(0));
    pthread_t tids[NUM];
    char labels[NUM];
    int t;
    for(t=0;t<NUM;t++){
        labels[t] = 'A' + t;   //'A'+0='A', 'A'+1='B'
        pthread_create(&tids[t], NULL, my_routine, &labels[t]);
    }
    int i;
    for(i=0;i<4;i++){
        printf("main: %d\n", i);
        usleep(rand() % (1000 * 1000));
    }
    pthread_exit(NULL);
    return 0;
}