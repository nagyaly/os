#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
int tickets = 10;
int flag[2];
sem_t sem;
void* thread0(void *args) {
  while (1) {
    sleep(1);               // force delay
    //====================== critical section start
    sem_wait(&sem);
    if(!tickets) break;
    tickets--;
    printf("Thread 1 sold 1 ticket, %d left\n", tickets);
    sem_post(&sem);
    //====================== critical section end
  }
  return NULL;
}
void* thread1(void *args) {
  while (1) {
    sleep(1);               // force delay
    //====================== critical section start
    sem_wait(&sem);
    if(tickets < 3) break;
    tickets--;
    printf("Thread 2 sold 1 ticket, %d left\n", tickets);
    sem_post(&sem);
    //====================== critical section end
  }
  return NULL;
}
int main(void) {
    //initialize semaphore (semaphore, 0/1 threads/processes, value)
    sem_init(&sem, 0, 1);
    pthread_t tid0, tid1;
    pthread_create(&tid0, NULL, thread0, NULL);
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_exit(NULL); // wait for all threads to exit
    sem_destroy(&sem);
    return 0;
}