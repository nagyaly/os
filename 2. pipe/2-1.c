#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFF_SIZE 20
#define R 0
#define W 1
int main() {
  int pipefd[2];
  pipe(pipefd);
  pid_t pid = fork();
  if (pid == 0) {
    close(pipefd[R]); // not needed
    // send string
    char *mess = "Hello World";
    write(pipefd[W], mess, BUFF_SIZE);
    // send int
    int number = 5;
    write(pipefd[W], &number, sizeof(int));
    close(pipefd[W]);
    return 0;
  } else {
    close(pipefd[W]); // not needed
    // receive string
    char buff[BUFF_SIZE];
    int bytes = read(pipefd[R], buff, BUFF_SIZE);
    printf("Received: %s %d\n", buff, bytes);
    // receive integer
    int number;
    int bytes2 = read(pipefd[R], &number, sizeof(int));
    printf("Received: %d %d\n", number, bytes2);
    close(pipefd[R]);
    wait(NULL);
  }
  return 0;
}

/*
(n * (n-1)) / 2			(fully connected)


declare array (40)
fork exactly 5 processes (5x2 pipes)
each process should receive its ID using pipe
each process will sum its portion from the array (40 / 5 = 8)
each process reply to the parent with the sub-sum
the parent will combine all the sub-sums to find the overall sum of the array
*/
