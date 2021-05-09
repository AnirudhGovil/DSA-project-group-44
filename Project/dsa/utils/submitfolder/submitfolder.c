#include "submitfolder.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
int submitfolder(char **args)
{
    char cmd1[10001];
    char cmd2[10001];
    char current_directory[1024];
    char download_directory[1024];
    getcwd(current_directory, 1023);
    char * file_name;
    strcpy(file_name,args[1]);
    char z = '/';
    // dowload_directory = 'Directory where the file need to be submitted';
    strcat(current_directory, z);
    strcat(current_directory,file_name);
    FILE* fileptr;
    fileptr = fopen(current_directory, "r") ;
    if(fileptr == NULL)
    {
        perror(current_directory);
        printf("No such File\n");
    }   
    else
    {
        FILE* zipptr;
        zipptr = CreateZip(fileptr);
        sprintf(cmd1, "mkdir %s/%s", download_directory, args[1]);
        system(cmd1);
        sprintf(cmd2, "cp -a %s. %s/%s", current_directory,download_directory , &zipptr); 
        system(cmd2);
        printf("%s is zipped and submmited in the download directory\n",args[1]);
        
    }
    
    return 1;
}
