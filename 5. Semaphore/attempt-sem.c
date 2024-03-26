#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
/*
    semaphore is an integer value...
    sem_wait        (try to enter CS)       decrement -> block
    sem_post        (declare exit of CS)    increment -> unblock
*/
sem_t sem;
int tickets = 10;
void* thread0(void *args) {
  while (tickets > 0) {
    //====================== critical section start
    sem_wait(&sem);                     //request CS (decrement)

    if(tickets > 0){
      usleep(0.25 * 1e6);               // force delay for 0.25 sec
      tickets--;
      printf("Thread 1 sold 1 ticket, %d left\n", tickets);
    }

    sem_post(&sem);                     //exit CS (increment)
    //====================== critical section end
  }
  return NULL;
}
void* thread1(void *args) {
  while (tickets > 0) {
    //====================== critical section start
    sem_wait(&sem);                     //request CS (decrement)

    if(tickets > 0){
      usleep(0.25 * 1e6);               // force delay for 0.25 sec
      tickets--;
      printf("Thread 2 sold 1 ticket, %d left\n", tickets);
    }

    sem_post(&sem);                     //exit CS (increment)
    //====================== critical section end
  }
  return NULL;
}
int main(void) {
    //initialize semaphore, (0 for threads, 1 for processes) (initial value)
    sem_init(&sem, 0, 1);
    pthread_t tid0, tid1;
    pthread_create(&tid0, NULL, thread0, NULL);
    pthread_create(&tid1, NULL, thread1, NULL);

    // wait for all threads to exit
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    printf("Tickets Left: %d\n", tickets);

    sem_destroy(&sem);
    return 0;
}