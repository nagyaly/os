#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define R 0
#define W 1
int main() {
  int pipefd1[2]; // from Parent to child
  int pipefd2[2]; // from child to parent
  pipe(pipefd1);
  pipe(pipefd2);
  pid_t pid = fork();
  if (pid == 0) {
    int number = 5123;
    write(pipefd2[W], &number, sizeof(int));
    read(pipefd1[R], &number, sizeof(int));
    printf("Received from parent: %d\n", number);
    close(pipefd1[R]);
    close(pipefd1[W]);
    close(pipefd2[R]);
    close(pipefd2[W]);
    return 0;
  } else {
    int number;
    read(pipefd2[R], &number, sizeof(int));
    printf("Received from child: %d\n", number);
    number = number * 2;
    write(pipefd1[W], &number, sizeof(int));
    close(pipefd1[R]);
    close(pipefd1[W]);
    close(pipefd2[R]);
    close(pipefd2[W]);
    wait(NULL);
  }
  return 0;
}
