#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int tickets = 10;
int turn = 0;
/*
  first attempt does not guarantee mutual exclusion
  each thread change turn to the other thread
  but the problem if on of the threads failed !
*/
void* thread0(void *args) {
  while (1) {
    //====================== critical section start
    while(turn != 0);
    if(tickets <= 0) break;
    usleep(0.25 * 1e6);               // force delay for 0.25 sec
    tickets--;
    printf("Thread 1 sold 1 ticket, %d left\n", tickets);
    turn = 1;
    //====================== critical section end
  }
  return NULL;
}
void* thread1(void *args) {
  while (1) {
    //====================== critical section start
    while(turn != 1);
    if(tickets <= 0) break;
    usleep(0.25 * 1e6);               // force delay for 0.25 sec
    tickets--;
    printf("Thread 2 sold 1 ticket, %d left\n", tickets);
    turn = 0;
    //====================== critical section end
  }
  return NULL;
}
int main(void) {
  pthread_t tid0, tid1;
  pthread_create(&tid0, NULL, thread0, NULL);
  pthread_create(&tid1, NULL, thread1, NULL);

  // wait for all threads to exit
  pthread_join(tid0, NULL);
  pthread_join(tid1, NULL);
  printf("Tickets Left: %d\n", tickets);

  return 0;
}