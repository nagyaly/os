#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 10
sem_t sem;
int* arr;
void display(){
    int i;
    for (i=0;i<SIZE;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void* thread_asc(void *args) {
    int i, j;
    sem_wait(&sem);
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(arr[i] < arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            usleep(500);
        }
    }
    sem_post(&sem);
    return NULL;
}
void* thread_desc(void *args) {
    int i, j;
    sem_wait(&sem);
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            usleep(500);
        }
    }
    sem_post(&sem);
    return NULL;
}
int main(void) {
    //initialize binary semaphore
    sem_init(&sem, 0, 1);
    arr = (int*) malloc(SIZE * sizeof(int));
    int i;
    srand(time(0));             //set seed with the current time in ms
    for (i=0;i<SIZE;i++){
        arr[i] = rand() % 10;
    }
    display();
    
    pthread_t tid0, tid1;
    pthread_create(&tid0, NULL, thread_asc, NULL);
    pthread_create(&tid1, NULL, thread_desc, NULL);
    
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);

    display();
    pthread_exit(NULL);
    free(arr);
    sem_destroy(&sem);
    return 0;
}