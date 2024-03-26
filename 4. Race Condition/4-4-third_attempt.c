#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int tickets = 10;
int flag[2];
/*
  third attempt guarantee mutual exclusion
  will result in a deadlock
*/
void* thread0(void *args) {
  while (1) {
    //====================== critical section start
		flag[0] = 1;							//say that thread0 is inside
    while(flag[1]);						//wait for thread1

    if(tickets <= 0) break;
    usleep(0.25 * 1e6);               // force delay for 0.25 sec

    tickets--;
		printf("Thread 1 sold 1 ticket, %d left\n", tickets);
    flag[0] = 0;						//say that thread0 finished
    //====================== critical section end
  }
  return NULL;
}
void* thread1(void *args) {
  while (1) {
    //====================== critical section start
		flag[1] = 1;							//say that thread1 is inside
    while(flag[0]);						//wait for thread0

    if(tickets <= 0) break;
    usleep(0.25 * 1e6);               // force delay for 0.25 sec

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
 
  // wait for all threads to exit
  pthread_join(tid0, NULL);
  pthread_join(tid1, NULL);
  printf("Tickets Left: %d\n", tickets);
 
  return 0;
}