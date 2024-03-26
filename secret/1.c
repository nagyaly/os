#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define SIZE 10
#define WORKERS 2
int main(){
    int i, arr[SIZE], total_sum = 0, id, sum = 0;
    int pipefd1[WORKERS][2]; // from Parent to childs    parent write, child read
    int pipefd2[WORKERS][2]; // from childs to parent    child write, parent read
    int portion = SIZE / WORKERS;
    int x = 0;
    for(i=0;i<SIZE;i++){
        arr[i] = 1 + rand() % 100;
        x += arr[i];
        printf("%d ", arr[i]);
    }
    printf("\n%d\n", x);
    for(i=0;i<WORKERS;i++){
        pipe(pipefd1[i]);
        pipe(pipefd2[i]);
        if(fork() != 0){
            read(pipefd1[i][0], &id, sizeof(int));
            for(i=id*portion;i<id*portion+portion;i++){
                sum += arr[i];
            }
            printf("pid: %d  id: %2d  sum: %d\n", getpid(), id, sum);
            write(pipefd2[i][1], &sum, sizeof(int));
            return 0;
        }
        write(pipefd1[i][1], &i, sizeof(int));
        read(pipefd2[i][0], &sum, sizeof(int));
        printf("sum: %d\n", sum);
        total_sum += sum;
    }
    for(i=0;i<WORKERS;i++){
        wait(NULL);
    }
    printf("total sum: %d\n", total_sum);

    return 0;
}