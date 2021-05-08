#include "setupfolder.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

node* InitNode(char* name, int space)
{
    node* new = (node*)(malloc(sizeof(node)));
    new->dir_name = name;
    new->depth = space;
    new->first_child = NULL;
    new->next_sibling = NULL;
    new->parent = NULL;
    return new;
}
void printNodes(tree folder, int space)
{
    
    node* temp = folder->first_child;
    if(temp == NULL)
    {
        return;
    }
    while(temp!=NULL)
    {
        for(int x=1;x<=space;x++)
            printf("\t");
        printf("%s\n", temp->dir_name);
        printNodes(temp,space+1);
        temp = temp->next_sibling;
    }
    

}

void MakeDir(char* path, char* dirName)
{

    if(mkdir(path, 0777) == -1)
        {
            if(errno == EINVAL)
            {
                fprintf(stderr,"Invalid Directory Name: %s\n", dirName);
                exit(EXIT_FAILURE);
            }
            else if(errno == EEXIST)
            {
                fprintf(stderr,"Directory name already in use: %s\n", dirName);
                exit(EXIT_FAILURE);
            }
            else 
            {
                fprintf(stderr,"Error on trying to create: %s\n", dirName);
                exit(EXIT_FAILURE);
            }
        }
}

void CreateFolder(tree folder, char* path)
{
    node* sub_folder = folder->first_child;
    if(sub_folder == NULL)
    {
        return;
    }
    while(sub_folder!=NULL)
    {
        int len1 = strlen(path);
        int len2 = strlen(sub_folder->dir_name);
        // path = (char*)(realloc(path,len1+len2+5));
        char* copy = (char*)(malloc(sizeof(char)*(len1+len2+5)));
        strcpy(copy, path);
        strcat(copy,"/");
        strcat(copy, sub_folder->dir_name);
        MakeDir(copy, sub_folder->dir_name); 

        CreateFolder(sub_folder, copy);
        sub_folder = sub_folder->next_sibling;
    }
    return;
}


int setupfolder(char **args)
{
    
    return 1;
    char filename[] = "/home/aarush/Downloads/setup.txt";
    FILE* fileptr;
    fileptr = fopen(filename, "r") ;
    if(fileptr == NULL)
    {
        perror(filename);
        printf("Cannot open File\n");
        //go error
    }   
    else
    {
        int position=0;
        int buffsize = 1024;
        char *buffer = (char *)malloc(sizeof(char) * buffsize);     
        char c;
        c = fgetc(fileptr);
        
        while(c!='\n' && c!=EOF)
        {
            buffer[position] = c;
            position++;
            if (position >= buffsize)
            {
                buffsize += 1024;
                buffer = (char *)realloc(buffer, buffsize);
                if (!buffer)
                {
                    fprintf(stderr, "dash: Allocation error\n");
                    exit(EXIT_FAILURE);
                }
            }
            c = fgetc(fileptr);
        }
        if(strcmp(buffer,args[1])!=0)
        {
            fprintf(stderr, "Argument and Parent Dirctory do not match!");
            exit(EXIT_SUCCESS);
        }
        if(c == EOF)
        {
            //NO DIRECTORY FORMED
        }
        // printf("Main Directory present in txt file\n");
        
        tree folder;
        folder = InitNode(buffer, 0);
        node* current = folder;
        c = fgetc(fileptr);
        while(c!=EOF)
        {
            buffsize = 1024;
            buffer = (char *)malloc(sizeof(char) * buffsize);     
            position=0;
            // printf("Hello1\n");
            int space_count = 0;
            while(c!='\n' && c!=EOF )
            {
                
                if(c == '\t')
                {
                    // printf("Hello_count1\n");
                    if(position == 0)
                        space_count++;
                }
                else
                {
                    // printf("Hello_count2\n");
                    buffer[position] = c;
                    position++;
                    if (position >= buffsize)
                    {
                        buffsize += 1024;
                        buffer = (char *)realloc(buffer, buffsize);
                        if (!buffer)
                        {
                            fprintf(stderr, "dash: Allocation error\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                c = fgetc(fileptr);
            }
            if(c!=EOF)
                c = fgetc(fileptr);

            if(current->depth < space_count-1)
            {
                perror("Incorrect directory format!\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                // printf("Hello2\n");
                node* new = InitNode(buffer, space_count);
                if(current->depth == space_count)
                {

                    //Add folder in same dir
                    // printf("Hello3\n");
                    current->next_sibling = new;
                    new->parent = current->parent;
                    current = new;
                }
                else if(current->depth < space_count)
                {
                    //Add sub-folder
                    // printf("Hello4\n");
                    new->parent = current;
                    current->first_child = new;
                    current = new;
                }
                else
                {
                    //traverse back to folder with same spaces
                    // printf("Hello5\n");
                    while(current->depth!=space_count)
                        current = current->parent;
                    current->next_sibling = new;
                    new->parent = current->parent;
                    current = new;
                }
            }

        }
        // printNodes(folder);
        DIR* dir = opendir(args[1]);
        if(dir!=NULL)
        {
            closedir(dir);
        }
        else if(errno == ENOENT)
        {
            MakeDir(args[1], args[1]);
        }   
        int len = strlen(args[1]);
        char* path = (char*)(malloc(sizeof(char)*(100000)));     
        path = args[1];
        // printNodes(folder,0);        
        CreateFolder(folder, path);       
        

        fclose(fileptr);
        return 1;
        
    }

}