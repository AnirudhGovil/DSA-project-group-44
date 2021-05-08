#include "createfolder.h"

int createfolder(char **args)
{
    const char cmd1[10001];
    const char cmd2[10001];
    char s1[1024];
    char d1[1024];
    strcpy(d1, "/home/vamsi/Downloads/dsa_assignment/");
    getcwd(s1, 1023);

    sprintf(cmd1, "mkdir %s/%s", s1, args[1]);
    system(cmd1);
    sprintf(cmd2, "cp -a %s. %s/%s", d1, s1, args[1]);
    system(cmd2);

    return 1;
}