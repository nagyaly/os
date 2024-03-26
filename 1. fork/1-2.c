#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
// compile code:	gcc 2.c -o 2
// run code: ./2
int main(void) {
  printf("STARTED\n");
  pid_t pid = fork();

  printf("%d %d\n", getpid(), getppid());
  printf("FINISED\n");
  wait(NULL);
  pid_t pid2 = fork();
  printf("%d %d\n", getpid(), getppid());
  wait(NULL);
  printf("THE END\n");
  return 0;
}
/*
	Main 7--8,FORK--10--11--13,FORK--14--15--16--17
 							    B)-------14--15--16--17
 					A)------10--11--13,FORK--14--15--16--17
								C)-------14--15--16--17
*/
