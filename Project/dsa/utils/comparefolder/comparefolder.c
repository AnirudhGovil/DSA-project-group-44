#include "comparefolder.h"

int comparefolder(char **args)
{
    // args[1] -> assignment 
    // args[2] -> zipfile
    char cmd1[10001];
    char cmd2[10001];
    char cmd3[10001];
    char current_directory[1024];
    char download_directory[1024];
    //getcwd(current_directory, 1023);
    // download_directory = " ";
    char * z = "/";
    FILE * fileptr;
    strcat(current_directory, z);
    strcat(current_directory,args[1]);
    fileptr = fopen(current_directory , "r");
    strcat(download_directory, z);
    strcat(download_directory,args[2]);
    if(fileptr == NULL){
        printf("NO SUCH FILE TO COMPARE\n");
    }
    else{
    sprintf(cmd1,"find /%s/ -type f -exec md5sum {} + | sort -k 2 > dir1.txt",current_directory);
    system(cmd1);
    sprintf(cmd2,"find /%s/ -type f -exec md5sum {} + | sort -k 2 > dir2.txt",download_directory);
    system(cmd2);
    sprintf(cmd3,"diff -r <dir1.txt> <dir2.txt>");
    system(cmd3);
    }
    return 0;
}


/* #include "comparefolder.h"

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int comparefolder(char **args)
{
    // args[1] -> assignment
    // args[2] -> zipfile
    char home_d[100001];
    char cmd1[100001];
    char cmd2[200002];
    char cmd3[300003];
    getcwd(home_d, 100001);
    if (chdir(args[1]) == -1)
    {
        printf("No such Folder\n");
        return 1;
    }
    chdir(home_d);
    if (!exists(args[2]))
    {
        printf("No such Folder\n");
        return 1;
    }

    sprintf(cmd1,"diff <(find %s -type f -exec md5sum {} + | sort -k 2) <(find %s -type f -exec md5sum {} + | sort -k 2)",args[1],args[2]);
    system(cmd1);
    sprintf(cmd2, "find %s -type f -exec md5sum {} + | sort -k 2 > dir2.txt", args[2]);
    system(cmd2);
    sprintf(cmd3, "diff -r <dir1.txt> <dir2.txt>");
    system(cmd3);
 
    return 0;
} */
