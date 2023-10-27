#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define NUM 6
typedef struct{
    char label;
    int limit;
    pthread_t prerequiste;
} Targs;
//----------------------------------------------
void* my_routine(void* raw_args){
    //convert pointer from void* to Targs*
    Targs* args = (Targs*) raw_args;
    //wait for a certain thread ???
    pthread_join(args->prerequiste, NULL);
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
        if(t % 2 != 0){     //1, 3, 5
            //1 depends on 0, 3 depends on 2, 5 depends on 4
            args[t].prerequiste = tids[t - 1];
        }
        pthread_create(&tids[t], NULL, my_routine, &args[t]);
    }
    int i;
    for(i=0;i<4;i++){
        printf("main: %d\n", i);
        usleep(rand() % (1000 * 1000));
    }
    pthread_exit(NULL);
    return 0;
}