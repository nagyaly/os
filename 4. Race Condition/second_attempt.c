#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int tickets = 10;
int flag[2];
/*
  second attempt does not guarantee mutual exclusion
  will result in a deadlock
*/
void* thread0(void *args) {
  while (1) {
    sleep(1);               // force delay
    //====================== critical section start
    while(flag[1]);						//wait for thread1
		flag[0] = 1;							//say that thread0 is inside
    if(!tickets) break;
    tickets--;
		printf("Thread 1 sold 1 ticket, %d left\n", tickets);
    flag[0] = 0;						//say that thread0 finished
    //====================== critical section end
  }
  return NULL;
}
void* thread1(void *args) {
  while (1) {
    sleep(1);               // force delay
    //====================== critical section start
    while(flag[0]);						//wait for thread0
		flag[1] = 1;							//say that thread1 is inside
    if(tickets < 3) break;
    tickets--;
		printf("Thread 2 sold 1 ticket, %d left\n", tickets);
    flag[1] = 0;							//say that thread1 finished
    //====================== critical section end
  }
  return NULL;
}
int main(void) {
  pthread_t tid0, tid1;
  pthread_create(&tid0, NULL, thread0, NULL);
  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_exit(NULL); // wait for all threads to exit
  return 0;
}