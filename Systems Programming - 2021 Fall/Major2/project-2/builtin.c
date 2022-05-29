#include "builtin.h"

/* Builtin Commands */
void cd(int argc, char *argv[]) {
	printf("CD\n");
}

void pwd() {
	int buff_size = 1024;
	char buf[buff_size];
    getcwd(buf, sizeof(buff_size)); // from <unistd.h>
    printf("%s\n", buf);
}

void userExit() {
	exit(EXIT_SUCCESS);
}

void path(int argc, char *argv[]) {
	printf("PATH\n");
}

void myhistory(int* historyCount,int* maxHistory, char**inputHistory,int argc, char *argv[]) {
	printf("DEBUG: historyCount: %d, maxHistory: %d\n",*historyCount,*maxHistory);
	printf("DEBUG 2: argc: %d, argv[1]: %s\n",argc,argv[1]);
	if(argc == 1) {
		if(*maxHistory < 21) {
			for(int i = 0; i < *historyCount; i++) {
				printf("[%d]: %s\n",i+1,inputHistory[i]);
			}
		} else {
			for(int i = 0; i < *historyCount; i++) {
				printf("[%d]: %s\n",(*maxHistory-20)+i+1,inputHistory[i]);
			}
		}
	} else {
		if((argv[1] ,"-c") == 0) {
			for(int i = 0; i < *historyCount; i++) {
				free(inputHistory[i]);
			}
			memset(inputHistory,0,sizeof(inputHistory));
			historyCount = 0;
			maxHistory = 0;
		}
		if((argv[1] ,"-e") == 0) { 
			
		}
	}
}