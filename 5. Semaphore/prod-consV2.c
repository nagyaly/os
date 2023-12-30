#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 10
int arr[SIZE];
int produced = 0;
int consumed = 0;
//===========>
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
    int* id = (int*) args;
    srand(time(0));
    while(1){
        //===========>
        if(produced >= SIZE){
            break;
        }
        arr[produced] = rand() % 100;
        printf("Producer %d [%d]: %d\n", *id, produced, arr[produced]);
        usleep(10000);
        produced++;
        //===========>
    }
    return NULL;
}
//----------------------------------------
void* consume(void* args){
    int* id = (int*) args;
    while(1){
        if(consumed >= SIZE){
            break;
        }
        printf("Consumed %d [%d]: %d\n", *id, produced, arr[consumed]);
        arr[consumed] = -1;
        usleep(500);
    }
    return NULL;
}
//----------------------------------------
int main(){
    //===========>
    //===========>
    pthread_t prod_th[2];
    int prod_ids[2] = {0, 1};
    pthread_create(&prod_th[0], NULL, produce, &prod_ids[0]);
    pthread_create(&prod_th[1], NULL, produce, &prod_ids[1]);

    pthread_t cons_th[2];
    int cons_ids[2] = {0, 1};
    pthread_create(&cons_th[0], NULL, produce, &cons_ids[0]);
    pthread_create(&cons_th[1], NULL, produce, &cons_ids[1]);
    // pthread_create(&tc, NULL, consume, NULL);

    pthread_join(prod_th[0], NULL);
    pthread_join(prod_th[1], NULL);
    pthread_join(cons_th[0], NULL);
    pthread_join(cons_th[1], NULL);
    // pthread_join(tc, NULL);
    display();
    //===========>
    //===========>
    return 0;
}