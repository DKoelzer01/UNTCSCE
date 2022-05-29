#ifndef ALIAS_H
#define ALIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PS1 "~> "
#define BUFFER_SIZE 1024
#define ALIAS_USAGE                                                \
    "Usage of alias:\n"                                            \
    "alias                      - Display a list of all aliases\n" \
    "alias alias_name='command' - Add a new alias\n"               \
    "alias -r alias_name        - Remove a single alias\n"         \
    "alias -c                   - Remove all aliases"

typedef struct Alias alias_t;
typedef struct Alias *alias_ptr_t;

// singly linked list to hold a list of alias names and commands
struct Alias
{
    char *name;
    char *command;
    alias_ptr_t next;
};

alias_ptr_t alias_create(char *name, char *command);
void alias_free(alias_ptr_t alias_ptr);
alias_ptr_t alias_destroy(alias_ptr_t alias_ptr);
alias_ptr_t alias_remove(alias_ptr_t alias_ptr, const char *name);
alias_ptr_t alias_add(alias_ptr_t alias_ptr, const char *name, const char *command);
void alias_display(const alias_ptr_t alias_ptr);
char *alias_query(const alias_ptr_t alias_ptr, const char *name);
alias_ptr_t execute_alias_command(char *command, alias_ptr_t alias_ptr);
void alias(char **command_buffer, int command_buffer_size);

#endif