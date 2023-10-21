#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  pid_t pid = fork();
  //-> child will start from here
  if (pid < 0) {
    perror("Fork Creation Failed\n");
    exit(1);
  }
  // child will see pid with the value 0
  if (pid == 0) {
    sleep(2);
    printf("In child: %d %d\n", getpid(), getppid());
		return 0; 		//end the exectution
  }
  // parent will see pid with actual value
  if (pid > 0) {
    printf("In Parent: %d %d\n", getpid(), getppid());
		// to avoid orphan process (child)
    wait(NULL);
    printf("All finished :)\n");
  }
	printf("THE END\n");
  return 0;
}
