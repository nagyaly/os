#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define THR_CNTS 4
int tickets = 10;
void *consume(void *args) {
  int *tid = (int *)args;
  while (tickets > 0) {
    sleep(1);               // force delay
    tickets--;              // critical section
    printf("Thread %d sold 1 ticket, %d left\n", *tid, tickets);
  }
  return NULL;
}
int main(void) {
  pthread_t tids[THR_CNTS];
  int ids[THR_CNTS];
  int i;
  for (i = 0; i < THR_CNTS; i++) {
    ids[i] = i;
    pthread_create(&tids[0], NULL, consume, &ids[i]);
  }
  pthread_exit(NULL); // wait for all threads to exit
  return 0;
}