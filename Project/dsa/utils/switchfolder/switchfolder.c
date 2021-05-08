#include "switchfolder.h"
int switchfolder(char **args)
{
    if (chdir(args[1]) == -1)
    {
        char address[200002];
        strcpy(address, "../");
        strcat(address, args[1]);
        if(chdir(address)==-1)
            printf("Directory not present\n");
    };

    return 1;
}