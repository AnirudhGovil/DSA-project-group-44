/////////////////////////////////////// MAIN FILE

#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>

/////////////////////////////////////// INCLUDING THE CUSTOM COMMANDS

#include "utils/switchfolder/switchfolder.h"
#include "utils/createfolder/createfolder.h"
#include "utils/updatefolder/updatefolder.h"
#include "utils/setupfolder/setupfolder.h"
#include "utils/testfolder/testfolder.h"
#include "utils/submitfolder/submitfolder.h"
#include "utils/comparefolder/comparefolder.h"
#include "utils/usefolder/usefolder.h"
#include "utils/parse/parse.h"
#include "utils/execute/execute.h"

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

/////////////////////////////////////// MAIN LOOP

int main()
{
    char cmd[100001];    // stores the input
    char *params[10001]; // stores the tokenised commands
    char use_string[100001]; // for the use function, to store the absolute path address of the folder to be 'used'
    char use_string_name[100001]; // for the use function, to store the name to be passed in the prompt
    int status = 1; // check which function has been called and whether any auxillary work has to be done in main()

    while (1)
    {
        // Print command prompt
        char directory[10001];
        getcwd(directory, 10001);
        printf("Group44Shell%s<%s>", directory,use_string_name);//use_string_name holds the name of the directory called by the 'use' function, blank otherwise

        // Read command from standard input
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
            break;

        // Split cmd into array of parameters
        parse(cmd, params, use_string);

        // Execute command
        int status = execute(params,commands_str,commands_func);

        switch (status)
        {
        case 1: // continue running shell
            continue;
        case 2: // use function has been called, store the directory address into use_string and name into use_string_name
            //getcwd(use_string,100001);
            strcpy(use_string,params[1]);
            strcpy(use_string_name,params[1]);
            chdir(directory); // since we want to remain in the same folder, we cd back to out original folder
            
            break;
        default:
            break;
        }
    }

    return 0;
}

/////////////////////////////////////// END