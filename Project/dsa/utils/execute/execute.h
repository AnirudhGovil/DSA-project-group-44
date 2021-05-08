#ifndef EXECUTE_H
#define EXECUTE_H

#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>

int execute(char **params, char*commands_str[], int (*commands_func[])(char **));

#endif