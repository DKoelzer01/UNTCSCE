#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	char * name;
	pid_t pid = fork();
	if(pid != 0) {
		printf("parent: %d started\n",getpid());
		printf("parent = %d\n",getppid());
	} else if(pid == 0) {
		printf("%d started\n",getpid());
		printf("child: parent = %d\n",getppid());
		printf("child: ...\n");
		sleep(20);
		printf("child: %d\n",getpid());
	} else {
		perror("fork error");
	}
}