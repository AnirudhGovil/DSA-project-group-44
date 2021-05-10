#include "comparefolder.h"

int comparefolder(char **args)
{
    // args[1] -> assignment 
    // args[2] -> zipfile
    char cmd1[20001];
    char cmd2[20001];
    char cmd3[10001];
    char home_d[1024];
    char dir1[10001];
    char dir2[10001];
    char download_directory[1024];
    getcwd(home_d, 1024);
    strcpy(download_directory,home_d);
    strcat(download_directory, "/Downloads/");
    if (chdir(args[1]) == -1)
    {
        printf("NO SUCH FILE TO COMPARE\n");
        return 1;
    }
    chdir(home_d);

    
    strcpy(dir1,home_d);
    strcat(dir1,"/");
    strcat(dir1,args[1]);

    strcpy(dir2,download_directory);
    strcat(dir2,"/");
    strcat(dir2,args[1]);
    strcat(dir2,".zip");


    sprintf(cmd1,"find /%s/ -type f -exec md5sum {} + | sort -k 2 > dir1.txt",dir1);
    system(cmd1);
    sprintf(cmd2,"find /%s/ -type f -exec md5sum {} + | sort -k 2 > dir2.txt",dir2);
    system(cmd2);
    sprintf(cmd3,"diff -r <dir1.txt> <dir2.txt>");
    system(cmd3);
    
    return 0;
}
