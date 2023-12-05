#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define SIZE 100
int flag[2]={0, 0};
int turn = 0;
int arr[SIZE];
void display(){
	int i;
    for(i=0;i<SIZE;i++){
		printf("%d ", arr[i]);
	}
    printf("\n");
}
void* sort_asc(void* arg){
	flag[1] = 1;
	turn = 0;
	while(flag[0] && turn==0);
	int i, j;
	for(i=0;i<SIZE-1;i++){
		for(j=i+1;j<SIZE;j++){
			if(arr[i] <= arr[j]){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
  	printf("Thread 0 Desc : ");
  	display();
	flag[1]=0;
	return NULL;
}
void* sort_desc(void* arg){
	flag[0] = 1;
	turn = 1;
	while(flag[1] && turn==1);
	int i, j;
	for(i=0;i<SIZE-1;i++){
		for(j=i+1;j<SIZE;j++){
			if(arr[i] >= arr[j]){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
  	printf("Thread 0 Asc : ");
  	display();
	flag[0] = 0;
	return NULL;
}
int main(){
	srand(time(NULL));
	int i;
	for(i=0;i<SIZE;i++){
		arr[i] = rand() % SIZE;
	}
	pthread_t tids[2];
	pthread_create(&tids[0], NULL, sort_asc, NULL);
	pthread_create(&tids[1], NULL, sort_desc, NULL);
	pthread_join(tids[0], NULL);
	pthread_join(tids[1], NULL);
	return 0;
}

