#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/*
    Race condition, shared resources/data
*/
int tickets = 10;
//------------------------------------------------------------
void* thread1(void* raw_args){
    while(tickets > 0){
        if(tickets > 0){
            usleep(100 * 1000);         //fake processing time
            tickets--;
            printf("Thread 1 sold 1 ticket, %d left\n", tickets);
        }
    }
    return NULL;
}
//------------------------------------------------------------
void* thread2(void* raw_args){
    while(tickets > 0){
        if(tickets > 0){
            usleep(100 * 1000);         //fake processing time
            tickets--;
            printf("Thread 2 sold 1 ticket, %d left\n", tickets);
        }
    }
    return NULL;
}
//------------------------------------------------------------
int main(){
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);                       //WAITING
    pthread_join(tid2, NULL);
    
    printf("Tickets Left: %d\n", tickets);
    return 0;
}