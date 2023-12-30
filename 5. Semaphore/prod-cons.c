#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 10
int arr[SIZE];
//----------------------------------------
void display(){
    int i;
    for (i=0;i<SIZE;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
//----------------------------------------
void* produce(void* args){
    int i;
    srand(time(0));
    for(i=0;i<SIZE;i++){
        //---->
        arr[i] = rand() % 100;
        printf("Producer: %d\n", arr[i]);
        usleep(500);
        //---->
        //---->
    }
    return NULL;
}
//----------------------------------------
void* consume(void* args){
    int i;
    for(i=0;i<SIZE;i++){
        //---->
        //---->
        printf("Consumer: %d\n", arr[i]);
        arr[i] = -1;
        usleep(500);
        //---->
    }
    return NULL;
}
//----------------------------------------
int main(){
    //---->
    //---->
    pthread_t tp, tc;
    pthread_create(&tp, NULL, produce, NULL);
    pthread_create(&tc, NULL, consume, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);
    display();
    //---->
    //---->
    return 0;
}