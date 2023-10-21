#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define SIZE 20
#define N 10
/*
  1-5   distribute array among processes
*/
int main(void) {
  printf("START\n");
  int i;
  int arr[SIZE];
  for (i = 0; i < SIZE; i++) {
    arr[i] = i + 1;
  }
  //-----------------------------
  int portion = SIZE / N;
  for (i = 0; i < N; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      int j, sum = 0;
      for (j = 0; j < portion; j++) {
        sum += arr[j + (i * portion)];
        sleep(1);
      }
      printf("Child: %d i: %d sum: %d\n", getpid(), i, sum);
      return 0;
    }
  }
  for (i = 0; i < N; i++) {
    wait(NULL);
  }
  return 0;
}