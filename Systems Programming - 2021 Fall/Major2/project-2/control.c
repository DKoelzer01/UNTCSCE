/* 
Anurodh Khatiwada ak0712
Daniel Koelzer dlk0138
Michael Laymon mal0420
Austin Leath azl0007

Group 7 - Project 2
Command Line Interpreter
11/22/2021

Control - Redirection and Pipelining
*/

#include "control.h"

/*
bool is_cd(char *input)
{
	bool exit = false;

	for (int i = 0; i < MAX_LETT; i++)
	{
		if (input[i] == 'c' && input[i + 1] == 'd')
			exit = true;
	}

	return exit;
}

void cd(char **parsed)
{
	if (parsed[1] == NULL)
	{
		fprintf(stderr, "Expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(parsed[1]) != 0)
		{
			fprintf(stderr, "Error to cd\n");
		}
	}
}



int is_Redirect(char *input)
{

	// loop through the input and checks for the redirection command
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == '>' || input[i] == '<')
			return 1;
	}
	return 0;
}

// function executes the redirectgion command when found
void execute_Redirect(char *input)
{

  char * parsed[] = { "sh", "-c", input, NULL };
  if (fork() == 0)  
	{
      int out = execvp(parsed[0], parsed);
      exit(1);
      if (out == -1) 
          exit(0);
  }
  else 
      wait(NULL);

}
*/

int control(int argc, char *argv[]) {
	for(int i = 0; i < argc; i++) {
		if(strchr(argv[i],'|') != NULL) {
			char* command1[512];
			char* command2[512];
			int pipePos = i;
			for(int j = 0; j < i; j++) {
				command1[j] = argv[j];
			}
			for( int j = i; j < argc; j++) {
				command1[j] = argv[j];
			}
			pipeline(command1,command2);
		}
	}
	return 0;
}

int pipeline(char* command1_parsed[], char* command2_parsed[]) {
	#ifdef DEBUG
	/**/printf("Pipe\n");
	#endif
	
	/* Reference: execvp()
		char* argument_list[] = {"ls", "-l", NULL}; // NULL terminated array of char* strings
		execvp("ls", argument_list);
		// executes `ls -l`
		// --man7.org
	*/
	
	// declare the pip file discriptor and child process ids
	int fd_pipe[2];
	pid_t pid1, pid2;
	
	// pipe encountered an error
	if ( pipe(fd_pipe) < 0 ) {
		printf("ERROR: Unable to create pipe!\n");
		return -1;
	}
	// pipe was successfully created
	else {
		#ifdef DEBUG
		/**/printf("DEBUG: Pipe created successfully.\n");
		#endif
	}
	
	pid1 = fork();
	// check if child process #1 is running
	if ( pid1 < 0 ) {
		// child process failed to create
		printf("ERROR: Unable to create child #1!\n");
		return -1;
	}
	else if ( pid1 == 0 ) {
		#ifdef DEBUG
		/**/printf("DEBUG: Child process #1 created successfully.\n");
		#endif
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO); // must use default standard output file descriptor number
		close(fd_pipe[1]);
		// launch execvp() in a new process
		if ( execvp( command1_parsed[0], command1_parsed ) < 0 ) { // execute command and arguments
			// execvp encountered an error
            printf("ERROR: Unable to run command #1!");
            return -1;
        }
	}
	else {
		// Parent executing
        pid2 = fork();
		if (pid2 < 0) {
			// child process failed to create
			printf("ERROR: Unable to create child #2!\n");
			return -1;
        }
		
		// Child 2 executing..
        if ( pid2 == 0 ) {
			#ifdef DEBUG
			/**/printf("DEBUG: Child process #2 created successfully.\n");
			#endif
            close(fd_pipe[1]);
            dup2(fd_pipe[0], STDIN_FILENO); // must use default standard input file descriptor number
            close(fd_pipe[0]);
			// launch execvp() in a new process
            if ( execvp( command2_parsed[0], command2_parsed ) < 0 ) { // execute command and arguments
				// execvp encountered an error
                printf("ERROR: Unable to run command #2!");
				return -1;
            }
        }
		else {
            // parent executing, waiting for two children
            wait(NULL); // wait for child #1
            wait(NULL); // wait for child #2
        }
	}
	return 0;
}