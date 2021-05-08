#include "createfolder.h"

int createfolder(char **args)
{
    char cmd1[10001];
    char cmd2[10001];
    char s1[1024];
    char d2[1024];
    char d1[1024];
    getcwd(s1, 1023); //to get the current working directory

    strcpy(d1, "/home/vamsi/Downloads/dsa_assignment/");
    //sprintf(d2,"%s/Downloads/",s1);

    sprintf(cmd1, "mkdir %s/%s", s1, args[1]);
    system(cmd1); //to create empty directory with name arg[1]

    sprintf(cmd2, "cp -a %s. %s/%s", d1, s1, args[1]); //to copy files from Downloads to newly created directory
    //sprintf(cmd2, "cp -a %s. %s/%s", d2, s1, args[1]);
    system(cmd2);

    return 1;
}