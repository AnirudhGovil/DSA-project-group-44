#ifndef SUBMITFOLDER_H
#define SUBMITFOLDER_H

// #include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
int submitfolder(char **args);
#endif
