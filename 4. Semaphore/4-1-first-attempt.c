#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/*
    first attempt
    each thread wait for his turn, and change/pass turn to the other after finishing

    Problem:
        if any thread failed, the other will be blocked permanently
*/
int tickets = 10;
int turn = 1;
int kill = 0;
//------------------------------------------------------------
void* thread1(void* raw_args){
    while(tickets > 0){
        while(turn != 1) ;       //busy waiting, if not thread 1 turn
        //==============================> CRITICAL SECTION
        if(tickets > 0){        //guard
            usleep(1000 * 1000);         //fake processing time
            tickets--;
            printf("Thread 1 sold 1 ticket, %d left\n", tickets);
        }
        if(kill) break;
        //==============================> CRITICAL SECTION
        turn = 2;               //switch turn to thread 2
    }
    return NULL;
}
//------------------------------------------------------------
void* thread2(void* raw_args){
    while(tickets > 0){
        while(turn != 2) ;       //busy waiting, if not thread 2 turn
        //==============================> CRITICAL SECTION
        if(tickets > 0){
            usleep(1000 * 1000);         //fake processing time
            tickets--;
            printf("Thread 2 sold 1 ticket, %d left\n", tickets);
        }
        //==============================> CRITICAL SECTION
        turn = 1;               //switch turn to thread 1
    }
    return NULL;
}
//------------------------------------------------------------
int main(){
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    usleep(2000 * 1000);
    printf("After 0.5 second\n");
    kill = 1;

    // pthread_join(tid1, NULL);                       //WAITING
    pthread_join(tid2, NULL);
    
    printf("Tickets Left: %d\n", tickets);
    return 0;
}

/*
    sem = 1         //only 1 thread can access the criticial section at once

    sem_wait();             --
    ================ CRITICAL SECTION
    sem_post();             ++
        sem++;


    how sem_wait(); is implemented
        while(sem == 0);            //wait for sem to increase
        //fail ???
        sem--;                      //decrement sem
*/