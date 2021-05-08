#include "switchfolder.h"
int switchfolder(char **args)
{
    if(chdir(args[1])==-1)
    {
        printf("Directory not present here\n");
    };
    return 1;
}