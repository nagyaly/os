#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
int tickets = 10;
void* thread0(void *args) {
  while (tickets > 0) {
    usleep(0.5 * 1e6);               // force delay for 0.5 sec
    //====================== critical section start
    if(tickets <= 0) break;
    tickets--;
    printf("Thread 0 sold 1 ticket, %d left\n", tickets);
    //====================== critical section end
  }
  return NULL;
}
void* thread1(void *args) {
  while (1) {
    //====================== critical section start
    if(tickets <= 0) break;
    usleep(0.5 * 1e6);               // force delay for 0.5 sec
    tickets--;
    printf("Thread 1 sold 1 ticket, %d left\n", tickets);
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