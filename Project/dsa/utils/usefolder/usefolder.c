#include "usefolder.h"
int usefolder(char **args)
{
    char address[100001];
    //store the absolute path address of the directory we wish to use
    strcpy(address,args[1]);
    chdir(address);
    return 2;
}