#include "usefolder.h"
int usefolder(char **args)
{
    chdir(args[1]);
    return 2;
}