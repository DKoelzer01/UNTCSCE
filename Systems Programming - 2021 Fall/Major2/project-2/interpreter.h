#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "control.h"
#include "builtin.h"
#include "alias.h"

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h> // execvp(), getcwd()

void sighandler(int sig);
pid_t branch(int *historyCount,int *maxHistoryCount, char**inputHistory, int argc, char *arg[]);
void newshell(int argc, char *argv[]);
int main(int argc, char *argv[]);

#endif