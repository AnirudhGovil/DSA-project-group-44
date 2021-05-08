#include "usefolder.h"
int usefolder(char **args)
{
    char address[100001];
    strcpy(address,args[1]);
    chdir(address);
    return 2;
}