#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int tickets = 10;
int turn = 0;
/*
  each thread change turn to the other thread
  but the problem if on of the threads failed !
*/
void* thread1(void *args) {
  while (tickets > 0) {
    sleep(1);               // force delay
    //====================== critical section start
    while(turn != 0);
    tickets--;
    turn = 1;
    //====================== critical section end
    printf("Thread 1 sold 1 ticket, %d left\n", tickets);
  }
  return NULL;
}
void* thread2(void *args) {
  while (tickets > 0) {
    sleep(1);               // force delay
    //====================== critical section start
    while(turn != 1);
    tickets--;
    turn = 0;
    //====================== critical section end
    printf("Thread 2 sold 1 ticket, %d left\n", tickets);
  }
  return NULL;
}
int main(void) {
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_create(&tid2, NULL, thread2, NULL);

  pthread_exit(NULL); // wait for all threads to exit
  return 0;
}