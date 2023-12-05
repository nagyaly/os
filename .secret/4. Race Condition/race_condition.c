#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define ARR_SIZE 100

int arr[ARR_SIZE];

void display_arr(){
    int i;
    for(i=0; i<ARR_SIZE; i++){
        printf(" %d", arr[i]);
    }
    printf("\n");
}
// Thread 0
void *sort_asc(void *arg){
    int i, j, temp;
    /** Enter CRITICAL SECTION **/
    for(i=0; i<ARR_SIZE-1; i++){
        for(j=i+1; j<ARR_SIZE; j++){
            if(arr[i] > arr[j]){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Thread 0 Ascending:");
    display_arr();
    /** Exit CRITICAL SECTION **/
    return NULL;
}
// Thread 1
void *sort_desc(void *arg){
    int i, j, temp;
    /** Enter CRITICAL SECTION **/
    for(i=0; i<ARR_SIZE-1; i++){
        for(j=i+1; j<ARR_SIZE; j++){
            if(arr[i] < arr[j]){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Thread 1 Descending:");
    display_arr();
    /** Exit CRITICAL SECTION **/
    return NULL;
}

int main(){

    srand(time(NULL));
    /* Main thread initializes array with random numbers */
    int i;
    for(i=0; i<ARR_SIZE; i++){
        arr[i] = rand() % ARR_SIZE;
    }
    printf("Main Thread:");
    display_arr();
    /* Main thread creates two threads */
    pthread_t t0, t1;
    pthread_create(&t0, NULL, sort_asc, NULL);
    pthread_create(&t1, NULL, sort_desc, NULL);
    /* Main thread waits the two threads to finish and join */
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

return 0;
}
