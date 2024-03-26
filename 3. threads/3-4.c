#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define NUM 5
//combine all arguments in 1 structure
typedef struct{
    char label;
    int limit;
} Targs;
//----------------------------------------------
void* my_routine(void* raw_args){
    //convert pointer from void* to Targs*
    Targs* args = (Targs*) raw_args;
    int i;
    for(i=0;i<args->limit;i++){
        printf("%c: %d / %d\n", args->label, i + 1, args->limit);
        usleep(rand() % (1000 * 1000));
    }
    return NULL;
}
int main(){
    srand(time(0));
    pthread_t tids[NUM];
    Targs args[NUM];            //array of structures
    int t;
    for(t=0;t<NUM;t++){
        args[t].label = 'A' + t;
        args[t].limit = 1 + rand() % 5;
        pthread_create(&tids[t], NULL, my_routine, &args[t]);
    }
    int i;
    for(i=0;i<4;i++){
        printf("main: %d\n", i);
        usleep(rand() % (1000 * 1000));
    }
    // wait for threads one by one
    for(i=0;i<NUM;i++){
        pthread_join(tids[i], NULL);
    }
    return 0;
}