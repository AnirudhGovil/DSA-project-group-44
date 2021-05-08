#include "createfolder.h"

int createfolder(char **args)
{
    char cmd1[10001];
    char cmd2[10001];
    char current_directory[1024];
    char download_directory2[1024];
    char download_directory1[1024];
    getcwd(current_directory, 1023); //to get the current working directory

    strcpy(download_directory1, "/home/vamsi/Downloads/dsa_assignment/");
    //sprintf(download_directory2,"%s/Downloads/",current_directory);

    sprintf(cmd1, "mkdir %s/%s", current_directory, args[1]);
    system(cmd1); //to create empty directory with name arg[1]

    sprintf(cmd2, "cp -a %s. %s/%s", download_directory1, current_directory, args[1]); //to copy files from Downloads to newly created directory
    //sprintf(cmd2, "cp -a %s. %s/%s", download_directory2, current_directory, args[1]);
    system(cmd2);
    printf("%s is created and downloaded the required files\n",args[1]);

    return 1;
}