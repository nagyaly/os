#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
void* my_routine(void* raw_args){
    char* c = (char*) raw_args;     //cast void* to char*
    int i;
    for(i=0;i<5;i++){
        //dereference the char* c to get the value
        printf("%c: %d\n", *c, i);
        sleep(1);
    }
    return NULL;
}
int main(){
    pthread_t tid1, tid2;
    char c1 = 'A', c2 = 'B';
    pthread_create(&tid1, NULL, my_routine, &c1);
    pthread_create(&tid2, NULL, my_routine, &c2);
    int i;
    for(i=0;i<5;i++){
        printf("main: %d\n", i);
        sleep(1);
    }
    pthread_exit(NULL);
    return 0;
}