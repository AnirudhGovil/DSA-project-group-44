// gcc -o shell *.c utils/comparefolder/*.* utils/createfolder/*.* utils/setupfolder/*.* utils/switchfolder/*.* utils/updatefolder/*.* utils/testfolder/*.* utils/submitfolder/*.* utils/usefolder/*.*
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/////////////////////////////////////// INCLUDING THE CUSTOM COMMANDS

#include "utils/switchfolder/switchfolder.h"
#include "utils/createfolder/createfolder.h"
#include "utils/updatefolder/updatefolder.h"
#include "utils/setupfolder/setupfolder.h"
#include "utils/testfolder/testfolder.h"
#include "utils/submitfolder/submitfolder.h"
#include "utils/comparefolder/comparefolder.h"
#include "utils/usefolder/usefolder.h"

/////////////////////////////////////// DEFINITIONS

#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"
#define TK_BUFF_SIZE 1024

/////////////////////////////////////// CUSTOM COMMANDS LISTS FOR ACCESSING THEM

char *commands_str[] = {
    "switch",
    "create",
    "update",
    "setup",
    "test",
    "submit",
    "compare",
    "use"};

int (*commands_func[])(char **) = {
    &switchfolder,
    &createfolder,
    &updatefolder,
    &setupfolder,
    &testfolder,
    &submitfolder,
    &comparefolder,
    &usefolder};

/////////////////////////////////////// DEFINING THE I/O FUNCTIONS

int execute(char **args)
{
    pid_t cpid;
    int status;

    /* for (int i = 0; i < sizeof(commands_str) / sizeof(char *); i++)
    {
        if (strcmp(args[0], commands_str[i]) == 0)
        {
            return (*commands_func[i])(args);
        }
    } */
    //If the **args i.e. input from the shell is a custom command, invoke it via (*commands_func[i])(args)

    cpid = fork();

    if (cpid == 0)
    {
        for (int i = 0; i < sizeof(commands_str) / sizeof(char *); i++)
        {
            if (strcmp(args[0], commands_str[i]) == 0)
            {
                return ((*commands_func[i])(args));
            }
        }

        if (execvp(args[0], args) < 0)
            printf("dash: command not found: %s\n", args[0]);
        exit(EXIT_FAILURE);
    }
    else if (cpid < 0)
        printf(RED "Error forking" RESET "\n");
    else
    {
        waitpid(cpid, &status, WUNTRACED);
    }
    return 1;
}

char **split_line(char *line)
{
    int buffsize = TK_BUFF_SIZE, position = 0;
    char **tokens = (char **)malloc(buffsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }
    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            tokens = (char **)realloc(tokens, buffsize * sizeof(char *));

            if (!tokens)
            {
                fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;

    return tokens;
}

char *read_line()
{
    int buffsize = 1024;
    int position = 0;
    char *buffer = (char *)malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
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
}

/////////////////////////////////////// MAIN LOOP

void loop()
{
    char *line;
    char **args;
    int status = 1;
    char use_string[1024];
    memset(use_string,0,1024);
    

    do
    {
        char directory[10001];
        getcwd(directory, 10001);
        printf("Group44Shell%s>", directory);
        line = read_line();
        args = split_line(line);
        if (!args[1])
        {
            args[1] = (char *)malloc(sizeof(char) * 10001);
            strcpy(args[1], use_string);
        }
        status = execute(args);
        if (status == 2)
        {
            strcpy(use_string, args[1]);
        }
        free(line);
        free(args);
    } while (status);
}

/////////////////////////////////////// MAIN

int main()
{
    loop();
    return 0;
}

/////////////////////////////////////// END