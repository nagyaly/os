#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int tickets = 10;
void* thread1(void *args) {
  while (1) {
    sleep(1);               // force delay
    if(!tickets) break;
    tickets--;              // critical section
    printf("Thread 1 sold 1 ticket, %d left\n", tickets);
  }
  return NULL;
}
void* thread2(void *args) {
  while (tickets > 0) {
    sleep(1);               // force delay
    if(!tickets) break;
    tickets--;              // critical section
    printf("Thread 2 sold 1 ticket, %d left\n", tickets);
  }
  return NULL;
}
int main(void) {
  pthread_t tid1, tid2;
  int i;
  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_create(&tid2, NULL, thread2, NULL);

  pthread_exit(NULL); // wait for all threads to exit
  return 0;
}