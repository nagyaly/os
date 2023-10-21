#include <stdio.h>
#include <unistd.h>

int main(void) {
  printf("%d %d\n", getpid(), getppid());
  unsigned long i, sum = 0;
  for (i = 0; i < 500000000; i++) {
    sum += i % 5;
  }
  printf("Sum: %ld\n", sum);
  return 0;
}