/*
Daniel Koelzer
dlk0138
2/22/2022
CSCE 4600 -- HW 1 Problem 2
Use the following System Calls at least once:
fork(); exit(); getpid(); getppid(); wait(); execl();
*/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main (int argc, char **argv) {
	if(fork() == 0) { 								//Child Process 1 -- Show PID and PPID
		printf("CHILD: Child started.\n");
		printf("CHILD INFORMATION\n");
		printf("PID: %d\n",getpid());				//Show PID
		printf("PPID: %d\n",getppid());				//Show PPID
		printf("CHILD: Finished execution, terminating.\n");
		printf("----------------------\n\n");
		exit(0);									//Kill child, return to parent
	} else { 										//Parent process
		printf("PARENT INFORMATION\n");
		printf("PID: %d\n",getpid());				//Show PID
		printf("PPID: %d\n",getppid());				//Show PPID
		printf("----------------------\n\n");
		printf("PARENT: Wait for the child process to terminate.\n");
		wait(NULL);									//Wait for any child process to end (Child process 1 in this case)
		printf("PARENT: Child terminated, resume execution.\n");
		printf("PARENT: Creating new child to execute outside program.\n");
		if(fork() == 0) {							//Child process 2 -- Run "ls -l"
			printf("CHILD: New child started.\n");
			printf("CHILD: Execute \"ls -l\".\n");
			execl("/bin/ls","ls","-l",(char *)NULL);//Execute ls -l using execl
			exit(0);								//Kill child 2
		} else {
			printf("PARENT: Wait for the child process to terminate.\n");
			wait(NULL);								//Wait for any child process to end (Child process 2 in this case)
			printf("PARENT: Child terminated, terminate parent.\n");
			exit(0);								//Terminate parent.
		}
	}
}