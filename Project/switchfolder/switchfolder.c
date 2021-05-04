#include "switchfolder.h"
int switchfolder(char **args)
{
    chdir(args[1]);
    return 1;
}