/* 
Anurodh Khatiwada ak0712
Daniel Koelzer dlk0138
Michael Laymon mal0420
Austin Leath azl0007

Group 7 - Project 2
Command Line Interpreter
11/22/2021

Interpreter
*/

/*
==========TODO==========
* CD function
* path command
* Redirection
* SIGSTOP Signal Control
* Implement Alias Support
* Complete Error handling
*/

#include "interpreter.h"
bool DEBUG_BOOL = 0;

pthread_cond_t cv;
pthread_mutex_t cv_mutex;
bool doExit = false;
int sigFlag = 0;
int status = 0;
int child = 0;
volatile sig_atomic_t interruptTerminal;
const char *builtInCMDS = "cd,exit,path,myhistory,newshell";

int main(int argc, char *argv[])
{
	char shellName[] = "SHELLNAME=SHELL\0";
	putenv(shellName);
	newshell(0, NULL);
	return 0;
}

void newshell(int argc, char *argv[])
{
	signal(SIGINT, sighandler);
	signal(SIGTERM, sighandler);
	signal(SIGTSTP, sighandler);
	signal(SIGSTOP, sighandler);
	signal(SIGCONT, sighandler);
	tcsetpgrp(0, getpgid(getpid()));
	printf("PID: %d, PARENT: %d, GROUP: %d\n",getpid(),getppid(),getpgid(getpid()));

	char shellPrompt[] = "Shell\0"; //Default shell name
	if (argc == 0)
	{					 //Only execute on first run
		char input[512]; //Input string
		printf("Would you like to customize your shell prompt for extra credit (Type y for yes): ");
		fgets(input, 512, stdin);
		if (toupper(input[0]) == 'Y')
		{
			printf("Type your customized shell prompt: ");
			fgets(shellPrompt, 512, stdin);
			shellPrompt[strcspn(shellPrompt, "\n")] = 0;
			setenv("SHELLNAME", shellPrompt, 1);
		}
	}
	char *inputHistory[20];							//History of commands executed
	int historyCount = 0;							//Number of commands in history buffer.
	int maxHistoryCount = 0;						//Number of commands previously executed
	char **command_buffer = malloc(sizeof(char *)); //Stores entire substrings of entire commands, delimited by semicolons.
	int command_buffer_pos = 0;
	int command_buffer_size = 1;
	char userInputRaw[512];					//Raw user input. No greater than 512 characters including \n.
	char const *temp = getenv("SHELLNAME"); //Get shell name from environment variable.
	if (temp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	char *shellName = getenv("SHELLNAME");
	FILE *batchFileIn;

	if (argc == 1)
	{
		printf("Interactive mode...\n");
	}
	else if (argc == 2)
	{
		printf("Batch mode...\n");
		batchFileIn = fopen(argv[1], "r");
		if (batchFileIn == NULL)
		{
			perror("File");
			exit(EXIT_FAILURE);
		}
	}
	while (true)
	{
		while (!interruptTerminal)
		{ //Asynch interrupt handling
			if (DEBUG_BOOL)
			{
				printf("DEBUG START LOOP\n");
			}
			command_buffer = malloc(sizeof(char *));
			command_buffer_pos = 0;
			command_buffer_size = 1;
			tcsetpgrp(0, getpgid(getpid()));
			memset(userInputRaw, 0, 512); //Reset user input
			if (argc == 0 || argc == 1)
			{							   //If interactive or default
				printf("%s: ", shellName); //Custom shell prompt output
				fgets(userInputRaw, 512, stdin);
				userInputRaw[strcspn(userInputRaw, "\n")] = 0;
			}
			else
			{ //If batch mode
				if (feof(batchFileIn))
				{						 //Check if end of file.
					fclose(batchFileIn); //Close file stream.
					argc = 1;			 //Force execution back to interactive mode.
				}
				else
				{
					fgets(userInputRaw, sizeof(userInputRaw), batchFileIn);
				}
			}
			historyCount++;	   //Increment history buffer #
			maxHistoryCount++; //Increment command count #
			if (historyCount > 20)
			{ //If more than 20 elements in history
				//Remove earliest element
				char *tempCharBuffer[20];
				for (int i = 0; i < 19; i++)
				{
					tempCharBuffer[i] = malloc(512);
					strcpy(tempCharBuffer[i], inputHistory[i + 1]);
				}
				tempCharBuffer[19] = malloc(512);
				strcpy(tempCharBuffer[19], userInputRaw);
				for (int i = 0; i < 20; i++)
				{
					strcpy(inputHistory[i], tempCharBuffer[i]);
					free(tempCharBuffer[i]);
				}
				historyCount--;
			}
			else
			{
				inputHistory[historyCount - 1] = malloc(sizeof(char) * strlen(userInputRaw));
				memcpy(inputHistory[historyCount - 1], userInputRaw, strlen(userInputRaw));
			}
			//Cut user input into individual "commands". Delimited by ; or \n
			while (1)
			{
				if (DEBUG_BOOL)
				{
					printf("DEBUG COMMAND PARSING\n");
				}
				char *pos = strchr(userInputRaw, ';'); //Find occurance of ;
				if (command_buffer_pos >= command_buffer_size)
				{ //Dynamic array resizing
					if (DEBUG_BOOL)
					{
						printf("DEBUG CURRENT SIZE: %d, NEW SIZE: %d\n", command_buffer_size, command_buffer_size + 1);
					}
					command_buffer_size += 1;
					command_buffer = realloc(command_buffer, command_buffer_size * sizeof(char *));
				}
				command_buffer[command_buffer_pos] = malloc(512 * sizeof(char));
				if (!pos)
				{ //If ; not found, copy rest of string
					strcpy(command_buffer[command_buffer_pos], userInputRaw);
					break;
				}
				else
				{ //If ; found, copy string before occurance to buffer, copy remaining string to userInputRaw
					strncpy(command_buffer[command_buffer_pos], userInputRaw, strlen(userInputRaw) - strlen(pos));
					char tempCharBuffer[512];
					strncpy(tempCharBuffer, pos + 1, strlen(pos));
					memmove(userInputRaw, tempCharBuffer, sizeof(tempCharBuffer));
				}
				command_buffer_pos++; //Move command_buffer_pos.
			}
			if (DEBUG_BOOL)
			{
				printf("DEBUG POST COMMAND PARSING\n");
			}
			if (DEBUG_BOOL)
			{
				for (int i = 0; i < command_buffer_size; i++)
				{
					printf("[%d]: %s\n", i, command_buffer[i]);
				}
			}
			//Clean begins/ends of strings. (Remove leading whitespace, remove trailing whitespace, remove ;)
			for (int i = 0; i < command_buffer_size; i++ )
			{
				if (command_buffer[i] == NULL)
				{
					break;
				}
				if (DEBUG_BOOL)
				{
					printf("DEBUG STRING CLEANING\n");
				}
				int start_itr = 0;
				int stop_itr = strlen(command_buffer[i]) - 1;
				while (isspace(command_buffer[i][start_itr]))
					start_itr++;
				while (stop_itr > start_itr && isspace(command_buffer[i][stop_itr]))
					stop_itr--;
				memmove(command_buffer[i], command_buffer[i] + start_itr, stop_itr + 1 - start_itr);
				command_buffer[i][stop_itr + 1 - start_itr] = 0;
			}
			if (DEBUG_BOOL)
			{
				printf("DEBUG POST STRING CLEANING\n");
			}
			if (DEBUG_BOOL)
			{
				for (int i = 0; i < command_buffer_size; i++)
				{
					printf("[%d]: %s\n", i, command_buffer[i]);
				}
			}
			alias(command_buffer,command_buffer_size);

			command_buffer_pos = 0;
			//Split commands into arguments
			while (command_buffer_size > 0)
			{
				if (DEBUG_BOOL)
				{
					printf("DEBUG CMD BUFFER PARSING\n");
				}
				if (argc == 2)
				{
					printf("Executing command: %s\n", command_buffer[0]);
				}
				char** arg_buffer = malloc(sizeof(char*)); //Stores individual commands and arguments
				int arg_buffer_pos = 0;
				int arg_buffer_size = 1;
				bool hasPipe = (strchr(command_buffer[command_buffer_pos],'|') != NULL);
				bool hasRedirect = (strchr(command_buffer[command_buffer_pos],'<') != NULL) || (strchr(command_buffer[command_buffer_pos],'>') != NULL);
				doExit = (strstr(command_buffer[command_buffer_pos],"exit") != NULL) || doExit;
				memset(arg_buffer,0,sizeof(arg_buffer));
				
				//Start parsing arguments
				while (1)
				{																	//Loop through current command string
					if(DEBUG_BOOL) { printf("DEBUG ARG PARSING\n");}
					if(DEBUG_BOOL) { printf("BUFFER: %s\n",command_buffer[command_buffer_pos]);}
					char* pos = strchr(command_buffer[command_buffer_pos],' ');
					if(DEBUG_BOOL) { printf("FOUND: %s\n",pos);}
					if(arg_buffer_pos > arg_buffer_size) {							//Resize dynamic buffer
						if(DEBUG_BOOL) { printf("DEBUG RESIZE ARG BUFFER\n");}
						if(DEBUG_BOOL) { printf("DEBUG ARG BUFFER SIZE: %d NOW %d\n",arg_buffer_size, arg_buffer_size + 1);}
						arg_buffer_size += 1;
						arg_buffer = realloc(arg_buffer,arg_buffer_size * sizeof(char*));
					}
					arg_buffer[arg_buffer_pos] = malloc(512 * sizeof(char));
					if(!pos) {														//If no more spaces found (end of string), copy entire remaining string
						memmove(arg_buffer[arg_buffer_pos],command_buffer[command_buffer_pos],strlen(command_buffer[command_buffer_pos]));
						break;
					}
					else
					{
						strncpy(arg_buffer[arg_buffer_pos], command_buffer[command_buffer_pos], strlen(command_buffer[command_buffer_pos]) - strlen(pos));
						char tempCharBuffer[512];
						strncpy(tempCharBuffer, pos + 1, strlen(pos));
						memmove(command_buffer[command_buffer_pos], tempCharBuffer, sizeof(tempCharBuffer));
						arg_buffer_size++;
					}
					arg_buffer_pos++;
				} //Command string parsed, execute command
				if (DEBUG_BOOL)
				{
					printf("DEBUG EXECUTE\n");
				}
				free(command_buffer[command_buffer_pos]);
				if (DEBUG_BOOL)
				{
					printf("DEBUG FREED\n");
				}
				command_buffer_size--;
				command_buffer_pos++;
				//Command split into arguments; Handle redirection and piping here;
				if (hasPipe || hasRedirect)
				{ //Pipelining and Redirection handled in Control.cpp
					control(arg_buffer_size, arg_buffer);
				}
				else
				{ //Normal execution
					if (DEBUG_BOOL)
					{
						printf("DEBUG BRANCH\n");
					}
					if (arg_buffer[0][0] != 0)
					{
						child = branch(&historyCount, &maxHistoryCount, inputHistory, arg_buffer_size, arg_buffer); //Create child process for command execution
						waitpid(child,&status,0);
					}
				}
			}
			free(command_buffer);
			if (doExit)
			{
				exit(EXIT_SUCCESS);
			}
		}
		interruptTerminal = 0;
		tcsetpgrp(0, getpgid(getpid()));
	}
}
pid_t branch(int *historyCount,int *maxHistoryCount, char**inputHistory, int argc, char *arg[])
{
	pid_t child_pid = fork();
	char *name = arg[0];
	arg[argc] = NULL;
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid > 0)
	{
		return child_pid;
	}
	else
	{
		if (strcmp(name, "cd") == 0)
		{
			cd(argc, arg);
		}
		else if (strcmp(name, "exit") == 0)
		{
			//Do nothing, handled with doExit flag.
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(name, "pwd") == 0)
		{
			pwd();
		}
		else if (strcmp(name, "path") == 0)
		{
			path(argc, arg);
		}
		else if (strcmp(name, "myhistory") == 0)
		{
			myhistory(historyCount, maxHistoryCount, inputHistory, argc, arg);
		}
		else if (strcmp(name, "newshell") == 0)
		{
			newshell(argc, arg);
		}
		else
		{
			execvp(name, arg);
			perror("");
		}
		exit(EXIT_SUCCESS);
	}
}

void sighandler(int sig)
{
	sigFlag = sig;
	if (sig == SIGINT)
	{ //Catch ^c
		interruptTerminal = 1;
		killpg(getpid(), SIGTERM);
		return;
	}
	if (sig == SIGTSTP)
	{ //Catch ^z
		interruptTerminal = 1;
		kill(child,SIGSTOP);
		status = 1;
		return;
	}
	if (sig == SIGTERM)
	{
		return;
	}
}