#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define N 5
/*
	to fork exactly n processes
*/
int main(void) {
  printf("START\n");
  int i;
  srand(time(0));
  for (i = 0; i < N; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      sleep(i); // simulate long operation
      printf("Child: %d STARTED\n", getpid());
      sleep(i); // simulate long operation
      printf("Child: %d END\n", getpid());
      return 0;
    }
  }
  for (i = 0; i < N; i++) {
    wait(NULL);
  }
  return 0;
}