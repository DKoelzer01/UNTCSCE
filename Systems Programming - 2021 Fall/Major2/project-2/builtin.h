#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // execvp(), getcwd()

void cd(int argc, char *argv[]);
void pwd();
void userExit();
void path(int argc, char *argv[]);
void myhistory(int* historyCount,int* maxHistory, char**inputHistory,int argc, char *argv[]);
#endif