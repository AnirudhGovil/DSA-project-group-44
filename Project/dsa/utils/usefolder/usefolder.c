#include "usefolder.h"
int usefolder(char **args)
{
    char address[100001];//stores the absolute path address of the directory we wish to use
    strcpy(address,args[1]);
    chdir(address);//we cd into the location so that in main() we can store the absolute location of this directory for later use
    return 2;// this number is unique to the use function
}