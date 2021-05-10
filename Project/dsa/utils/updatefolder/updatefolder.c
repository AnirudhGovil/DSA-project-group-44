/* #include "updatefolder.h"
int updatefolder(char **args)
{
    char cmd1[20001];
    char cmd2[50001];
    char current_directory[10001];
    char download_directory2[20001];
    char download_directory1[10001];
    getcwd(current_directory, 10001); //to get the current working directory

    //strcpy(download_directory1, "/home/vamsi/Downloads/dsa_assignment/");
    sprintf(download_directory2,"%s/Downloads/",current_directory);

    sprintf(cmd1, "rm -r %s/%s/dist", current_directory, args[1]);
    int i=system(cmd1); //to delete old dist files in directory arg[1]

    //sprintf(cmd2, "cp -a %s. %s/%s", download_directory1, current_directory, args[1]); //to copy files from Downloads to newly created directory
    sprintf(cmd2, "cp -a %s. %s/%s", download_directory2, current_directory, args[1]);
    if(i==0)
        system(cmd2);
    if(i==0)
        printf("%s is updated, old files are deleted & new files are downloaded\n",args[1]);
    return 1;
} */

#include "updatefolder.h"
int updatefolder(char **args)
{
    char cmd1[20001];
    char cmd2[50001];
    char current_directory[10001];
    char download_directory2[20001];
    char download_directory1[10001];
    getcwd(current_directory, 10001); //to get the current working directory

    if (chdir("Downloads") == -1)
    {
        printf("Downloads folder is not present in this directory\n"); // checking i fthe required flder is present
        chdir(current_directory);
        return 1;
    }
    chdir(current_directory);

    sprintf(cmd1, "rm -r %s/dist", args[1]);
    //sprintf(cmd1, "rm  %s/problem_set.pdf", args[1]);
    int i = system(cmd1); //to delete old dist files in directory arg[1]

    chdir("Downloads");
    //sprintf(cmd2, "cp -R local_assignment/. ../%s/",args[1]);
    //system(cmd2);
    sprintf(cmd2, "cp -a dist ../%s/",args[1]); // copy dist files
    if (i == 0)
        system(cmd2);
    sprintf(cmd2, "cp -a problem_set.pdf ../%s",args[1]); // copy problem set
    if (i == 0)
        system(cmd2);
    if (i == 0)
        printf("%s is updated, old files are deleted & new files are downloaded\n", args[1]);
    chdir(current_directory);
    return 1;
}