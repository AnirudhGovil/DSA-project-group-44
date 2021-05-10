#include "testfolder.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int testfolder(char **args)
{
    int position=0;
    int buffsize = 1024;
    char *buffer = (char *)malloc(sizeof(char) * buffsize);     //stores path to submitter.py
    if (!buffer)    //check if memory is allocated
    {
        fprintf(stderr, "Group44Shell: Allocation error\n");
        exit(EXIT_FAILURE);
    }
    char c;
    while (1)   //gets the argument <assignment>
    {
        c = args[1][position];
        if (c == '\0')
        {
            break;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= buffsize-50)
        {
            buffsize += 1024;
            buffer = (char *)realloc(buffer, buffsize);

            if (!buffer)
            {
                fprintf(stderr, "Group44Shell: Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    buffer[position] = '\0';
    strcat(buffer, "/dist/submitter.py");   //append remaining path

    FILE *file;
    if (file = fopen(buffer, "r"))      //check if submitter.py is present
    {
        fclose(file);
        
        char* new_buffer = (char *)malloc(sizeof(char) * buffsize); //contains the command line to run submitter.py
        if (!new_buffer) 
        {
            fprintf(stderr, "Group44Shell: Allocation error\n");
            exit(EXIT_FAILURE);
        }
        
        char* command = "unbuffer python3 ";
        strcpy(new_buffer,command);
        strcat(new_buffer,buffer);
        strcat(new_buffer, "| perl -pe 's/\e\\[?.*?[\\@-~]//g' > testLog.txt"); //directs output to txt file and removes color codes from the text

        system(new_buffer);     //executes the command on terminal

        printf("Submitter executed. Output stored in testLog.txt\n");     
        free(new_buffer); 

    }
    else
    {
        printf("Cannot test. submitter.py file does not exist.\n");
    }
    free(buffer);
        
    return 1;
}