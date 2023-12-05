#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int tickets = 10;
void* thread0(void *args) {
  while (1) {
    sleep(1);               // force delay
    //====================== critical section start
    if(!tickets) break;
    tickets--;
    printf("Thread 1 sold 1 ticket, %d left\n", tickets);
    //====================== critical section end
  }
  return NULL;
}
void* thread1(void *args) {
  while (tickets > 0) {
    sleep(1);               // force delay
    //====================== critical section start
    if(!tickets) break;
    tickets--;
    printf("Thread 2 sold 1 ticket, %d left\n", tickets);
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