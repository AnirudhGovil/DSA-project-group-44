#include "submitfolder.h"

/* int submitfolder(char **args)
{
    char cmd1[10001];
    char cmd2[10001];
    char cmd3[10001];
    char current_directory[1024];
    char download_directory[1024];
    getcwd(current_directory, 1023);
    char * file_name = (char*)malloc(200002*sizeof(char));
    strcpy(file_name,args[1]);
    char * z = "/";
    // download_directory = "Directory where the file need to be submitted";
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
        sprintf(cmd1,"zip -q %s.zip %s ",file_name ,file_name );
        system(cmd1);
        strcat(file_name, ".zip");
        sprintf(cmd2, "mkdir %s/%s", download_directory, file_name);
        system(cmd2);
        sprintf(cmd3, "cp -a %s. %s/%s", current_directory,download_directory , file_name); 
        system(cmd3);
        printf("%s is zipped and submmited in the download directory\n",args[1]);
        
    }
    
    return 1;
}
 */

int submitfolder(char **args)
{
    char home_d[100001];
    char cmd1[100001];
    char cmd2[200002];
    getcwd(home_d, 100001);
    if (chdir(args[1]) == -1)
    {
        printf("No such Folder\n");
        return 1;
    }
    chdir(home_d);

    strcat(cmd1, args[1]);
    strcat(cmd1, ".zip");
    sprintf(cmd2, "zip -r %s %s", cmd1, args[1]);
    system(cmd2);

    return 1;
}