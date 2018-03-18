#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char **argv)
{
	int pid;

	pid = fork();

	if (pid == 0) {
	execv("Child", NULL);
	}

	if(pid > 0){
          wait(NULL);
        }

	return 0;
}
