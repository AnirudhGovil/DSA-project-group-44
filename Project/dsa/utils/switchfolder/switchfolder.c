#include "switchfolder.h"
int switchfolder(char **args)
{
    if (chdir(args[1]) == -1)//if the folder is not withing the current directory we check if it is at the same depth as we are currently
    {
        char address[200002];
        strcpy(address, "../");// to check if it is a sibling folder, check the ../ directory
        strcat(address, args[1]);
        if(chdir(address)==-1)// this means that the folder is not at the same depth as us (sibling folders) or under us (child folder)
            printf("Directory not present\n");
    };

    return 1;
}