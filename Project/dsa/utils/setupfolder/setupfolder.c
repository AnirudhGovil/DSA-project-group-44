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

node* InitNode(char* name, int space)               // creates and initialises a new node of the directory tree
{
    node* new = (node*)(malloc(sizeof(node)));
    if (!new)
    {
        fprintf(stderr, "Group44Shell: Allocation error\n");
        exit(EXIT_FAILURE);
    }
    new->dir_name = name;
    new->depth = space;
    new->first_child = NULL;
    new->next_sibling = NULL;
    new->parent = NULL;
    return new;
}
void printNodes(tree folder, int space)             // prints the tree in an indented format
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

    if(mkdir(path, 0777) == -1)     // create a new directory with given path and name. 
    {                               // returns 0 if directory is created
        if(errno == EINVAL)
        {
            fprintf(stderr,"Invalid Directory Name: %s\n", dirName);
            return;
        }
        else if(errno == EEXIST)
        {
            fprintf(stderr,"Directory name already in use: %s\n", dirName);
            return;
        }
        else 
        {
            fprintf(stderr,"Error on trying to create: %s\n", dirName);
            return;
        }
    }
}

void CreateFolder(tree folder, char* path)      // traverse through the whole tree and make directories
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

        path = (char*)(realloc(path,len1+len2+5));  //contains the path to the present subfolder
        if (!path)
        {
            fprintf(stderr, "Group44Shell: Allocation error\n");
            exit(EXIT_FAILURE);
        }

        char* copy = (char*)(malloc(sizeof(char)*(len1+len2+5)));   //contains the path to the sub-folders of the present folder
        if (!copy)
        {
            fprintf(stderr, "Group44Shell: Allocation error\n");
            exit(EXIT_FAILURE);
        }

        strcpy(copy, path);
        strcat(copy,"/");
        strcat(copy, sub_folder->dir_name);

        MakeDir(copy, sub_folder->dir_name); //create a directory with given path and name

        CreateFolder(sub_folder, copy);     //recursively call for next subfolder
        sub_folder = sub_folder->next_sibling;
    }
    return;
}


int setupfolder(char **args)
{

    char filename[] = "Downloads/setup.txt";  //**Path for the indented file to be read**//
    FILE* fileptr;
    fileptr = fopen(filename, "r") ;
    if(fileptr == NULL)
    {
        perror(filename);
        printf(" Cannot open setup.txt\n");     //file not present or cannot open it
    }   
    else
    {
        int position=0;
        int buffsize = 1024;
        char *buffer1 = (char *)malloc(sizeof(char) * buffsize);    //stores the first name from the txt file
        if (!buffer1)
        {
            fprintf(stderr, "Group44Shell: Allocation error\n");
            exit(EXIT_FAILURE);
        }     
        char c;
        while(c!='\n' && c!=EOF)
        {
            buffer1[position] = c;
            position++;
            if (position >= buffsize)
            {
                buffsize += 1024;
                buffer1 = (char *)realloc(buffer1, buffsize);
                if (!buffer1)
                {
                    fprintf(stderr, "Group44Shell: Allocation error\n");
                    exit(EXIT_FAILURE);
                }
            }
            c = fgetc(fileptr);
        }
        buffer1[position] = '\0';


        if(c == EOF)    //checks if a dir name is present except root directory
        {
            printf("No Directory present in txt file!\n");
            return 1;
        }
        
        tree folder; //stores pointer to a tree corresponding to the given structure

        folder = InitNode(buffer1, 0); //create a root node in the tree

        node* current = folder;
        c = fgetc(fileptr);

        while(c!=EOF)
        {
            buffsize = 1024;
            char* buffer2 = (char *)malloc(sizeof(char) * buffsize);     //stores the names of directories
            position=0;
            int space_count = 0;    //counts the number of tab characters before the text
            while(c!='\n' && c!=EOF )
            {
                
                if(c == '\t')
                {
                    if(position == 0)
                        space_count++;
                }
                else
                {
                    buffer2[position] = c;
                    position++;
                    if (position >= buffsize)
                    {
                        buffsize += 1024;
                        buffer2 = (char *)realloc(buffer2, buffsize);
                        if (!buffer2)
                        {
                            fprintf(stderr, "Group44Shell: Allocation error\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                c = fgetc(fileptr);
            }
            buffer2[position] = '\0';

            if(c!=EOF)
                c = fgetc(fileptr);

            if(current->depth < space_count-1)      //diff between number of tabs between any directory ad its previous one in txt < 2
            {
                perror("Incorrect directory format!\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                node* new = InitNode(buffer2, space_count); //create node with given name and space count

                if(current->depth == space_count)
                {
                    //Add folder in same dir
                    current->next_sibling = new;
                    new->parent = current->parent;
                    current = new;
                }
                else if(current->depth < space_count)
                {
                    //Add sub-folder
                    new->parent = current;
                    current->first_child = new;
                    current = new;
                }
                else
                {
                    //traverse back to folder with same spaces
                    while(current->depth!=space_count)
                        current = current->parent;
                    current->next_sibling = new;
                    new->parent = current->parent;
                    current = new;
                }
            }
        }

        DIR* dir = opendir(args[1]);    
        if(dir!=NULL)   //checks if a dir with given root name is already present
        {
            closedir(dir);
        }
        else if(errno == ENOENT)
        {
            MakeDir(args[1], args[1]); //if not present, then create a dir
        }   
        int len = strlen(args[1]);

        char* path = (char*)(malloc(sizeof(char)*(1024)));     
        strcpy(path, args[1]);

        CreateFolder(folder, path);  //create a folder structure with given root directory

        printf("Folder structure created!\n");

        free(buffer1);
        free(path);

        fflush(stdin);
        fclose(fileptr);
        return 1;
        
    }

}