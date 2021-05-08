#ifndef PARSE_H
#define PARSE_H

#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>

void parse(char *cmd, char **params, char *use_string);

#endif