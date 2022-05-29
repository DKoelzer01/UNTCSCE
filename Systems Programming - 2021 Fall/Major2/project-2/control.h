#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // execvp(), getcwd()
#include <sys/wait.h>

int redirection();
int pipeline(char* command1_parsed[], char* command2_parsed[]);
int control(int argc, char *argv[]);

#endif