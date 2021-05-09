#include "createfolder.h"

int createfolder(char **args)
{
    char cmd1[100001];
    char cmd2[100001];
    char current_directory[100001];
    char download_directory2[100001];
    char download_directory1[100001];
    getcwd(current_directory, 100001); //to get the current working directory

    //strcpy(download_directory1, "/home/vamsi/Downloads/dsa_assignment/");
    sprintf(download_directory2,"%s/Downloads/",current_directory);

    sprintf(cmd1, "mkdir %s/%s", current_directory, args[1]);
    int i=system(cmd1); //to create empty directory with name arg[1]

    //sprintf(cmd2, "cp -a %s. %s/%s", download_directory1, current_directory, args[1]); //to copy files from Downloads to newly created directory
    sprintf(cmd2, "cp -a %s. %s/%s", download_directory2, current_directory, args[1]);
    system(cmd2);
    if(i==0)
    printf("%s is created and downloaded the required files\n",args[1]);

    return 1;
}