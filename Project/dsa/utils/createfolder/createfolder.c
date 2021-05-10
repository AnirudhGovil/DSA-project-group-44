#include "createfolder.h"

int createfolder(char **args)
{
    char cmd1[20001];
    char cmd2[50001];
    char current_directory[10001];
    char download_directory2[20001];
    char download_directory1[10001];
    getcwd(current_directory, 10001); //to get the current working directory

    if (chdir("Downloads") == -1)
    {
        printf("Downloads folder is not present in this directory\n");
        chdir(current_directory);
        return 1;
    }
    chdir(current_directory);
    
    sprintf(cmd1, "mkdir %s", args[1]);
    int i = system(cmd1); //to create empty directory with name arg[1]

    chdir("Downloads");
    //sprintf(cmd2, "cp -R local_assignment/. ../%s/",args[1]);
    //system(cmd2);
    sprintf(cmd2, "cp -a dist ../%s",args[1]); // copy dist files
    system(cmd2);
    sprintf(cmd2, "cp -a problem_set.pdf ../%s",args[1]);// copy problemm set
    system(cmd2);
    chdir(current_directory);
    if (i == 0)
        printf("%s is created and downloaded the required files\n", args[1]);

    return 1;
}