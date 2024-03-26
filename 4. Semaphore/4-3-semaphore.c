#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define TCOUNT 5
sem_t sem;              //semaphore
int tickets = 25;
//------------------------------------------------------------
void* thread(void* raw_args){
	int* id = (int*) raw_args;
	printf("Thread %d Started\n", *id);
	while(tickets > 0){
			usleep(10 * 1000);         //fake processing time
			sem_wait(&sem);
			//==============================> CRITICAL SECTION
			if(tickets > 0){							//GUARD
					usleep(10 * 1000);         //fake processing time
					tickets--;
					printf("Thread %d sold 1 ticket, %d left\n", *id, tickets);
			}
			//==============================> CRITICAL SECTION
			sem_post(&sem);
	}
	printf("Thread %d Finished\n", *id);
	return NULL;
}
//---------------------------------------------------------
int main(){
    //  0: threads, 1: processes,   value
    sem_init(&sem, 0, 1);           //binary semaphore
    pthread_t tids[TCOUNT];
		int ids[TCOUNT];
		int i;
		for(i=0;i<TCOUNT;i++){
			ids[i] = i + 1;
	    pthread_create(&tids[i], NULL, thread, &ids[i]);
		}
		for(i=0;i<TCOUNT;i++){
    	pthread_join(tids[i], NULL);
		}
    printf("Tickets Left: %d\n", tickets);
    sem_destroy(&sem);
    return 0;
}