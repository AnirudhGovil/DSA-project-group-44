#include "comparefolder.h"

int comparefolder(char **args)
{
    // args[1] -> assignment 
    // args[2] -> zipfile
    char cmd1[10001];
    char cmd2[10001];
    char cmd3[10001];
    char cmd4[10001];
    char cmd5[10001];
    char cmd6[10001];
    char home_d[1024];
    char dir1[1024];
    char dir2[1024];
    char tempdir[1024];
    char tempcmd[10001];
    char download_directory[1024];
    strcpy(tempdir,args[2]);
    strcat(tempdir,".zip");
    getcwd(home_d, 1024);
    strcpy(download_directory,home_d);
    strcat(download_directory, "/Downloads/");
    if (chdir(args[1]) == -1)
    {
        printf("NO SUCH FILE TO COMPARE\n");
        return 1;
    }
    sprintf(tempcmd , "cd Downloads/");
    system(tempcmd);
    if (chdir(tempdir) == -1)
    {
        printf("NO SUCH ZIPPED FILE TO COMPARE\n");
        return 1;
    }
    sprintf(tempcmd , "cd ..");
    system(tempcmd);

    chdir(home_d);
    strcpy(dir1,home_d);
    strcat(dir1,"/");
    strcat(dir1,args[1]);

    strcpy(dir2,download_directory);
    strcat(dir2,"/");
    strcat(dir2,args[1]);
    strcat(dir2,".zip");

    sprintf(tempcmd , "cd Downloads/");
    system(tempcmd);
    sprintf(tempcmd , "unzip -q %s.zip" , args[2]);
    system(tempcmd);
    sprintf(tempcmd , "ls %s/ > dir1.txt" , args[2]);
    system(tempcmd);
    sprintf(tempcmd , "mv dir1.txt ../");
    system(tempcmd);
    sprintf(tempcmd , "rm -r %s",args[2]);
    system(tempcmd);
    sprintf(tempcmd , "cd ..");
    system(tempcmd);
    sprintf(cmd1 , "ls %s/ > dir2.txt" , args[1]);
    system(cmd1);
    sprintf(cmd2 , "sort dir1.txt > sorteddir1.txt");
    system(cmd2);
    sprintf(cmd3 , "sort dir2.txt > sorteddir2.txt");
    system(cmd3);
    sprintf(cmd4 , "if diff sorteddir1.txt sorteddir2.txt > /dev/null ; then echo ' NO DIFFERENCE. BOTH FOLDER HAVE SAME FILES ' ; else echo 'EXTRA FILES IN ZIPPED FOLDER ARE: '; comm -23 sorteddir1.txt sorteddir2.txt; fi");
    system(cmd4);
    sprintf(cmd5 , "rm dir1.txt dir2.txt");
    system(cmd5);
    sprintf(cmd6 , "rm sorteddir1.txt sorteddir2.txt");
    system(cmd6);
    
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
