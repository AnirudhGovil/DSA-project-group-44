
//Main loop that takes inputs and parses them

/*******************************************************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/*******************************************************************************************************************/

#include "switchfolder/switchfolder.h"
#include "createfolder/createfolder.h"
#include "updatefolder/updatefolder.h"
#include "setupfolder/setupfolder.h"
#include "testfolder/testfolder.h"
#include "submitfolder/submitfolder.h"
#include "comparefolder/comparefolder.h"
#include "usefolder/usefolder.h"
#include "exitshell/exitshell.h"

/*******************************************************************************************************************/

/**
  @brief List of command names.
 */
char *commands_str[] = {
    "switch",
    "create",
    "update",
    "setup",
    "test",
    "submit",
    "compare",
    "use",
    "exit"};

/**
  @brief List of command function pointers corresposding to the previous names.
 */
int (*commands_func[])(char **) = {
    &switchfolder,
    &createfolder,
    &updatefolder,
    &setupfolder,
    &testfolder,
    &submitfolder,
    &comparefolder,
    &usefolder,
    &exitshell};

/*******************************************************************************************************************/

/**
  @brief Launch a program and wait for it to terminate.
  @param arguments Null terminated list of command + arguments.
  @return Always returns 1, to continue execution.
 */
int launch(char **arguments)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0)
  {
    // Child process
    if (execvp(arguments[0], arguments) == -1)
    {
      perror("Error");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    // Error forking
    perror("Error");
  }
  else
  {
    // Parent process
    do
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
   @brief Execute shell built-in or launch command.
   @param arguments Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int execute(char **arguments)
{

  if (arguments[0] == NULL)
  {
    // An empty command was entered.
    return 1;
  }

  for (int i = 0; i < sizeof(commands_str) / sizeof(char *); i++)
  {
    if (strcmp(arguments[0], commands_str[i]) == 0)
    {
      return (*commands_func[i])(arguments);
    }
  }

  return launch(arguments);
}

/*******************************************************************************************************************/

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us

  if (getline(&line, &bufsize, stdin) == -1)
  {
    if (feof(stdin))
    {
      exit(EXIT_SUCCESS); // We recieved an EOF
    }
    else
    {
      exit(EXIT_FAILURE);
    }
  }

  return line;
}

/*******************************************************************************************************************/

/**
   @brief Split a line into tokens.
   @param line The input on the shell.
   @return Null-terminated array of tokens.
 */
char **tokeniser(char *line)
{
  int bufsize = 64;
  char **tokens = malloc(bufsize * sizeof(char *));

  if (!tokens)
  {
    fprintf(stderr, "allocation error\n");
    exit(EXIT_FAILURE);
  }

  int position = 0;
  char *token;
  token = strtok(line, "\t\n");
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position >= bufsize)
    {
      bufsize += 64;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens)
      {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, "\t\n");
  }
  tokens[position] = NULL;
  return tokens;
}

/*******************************************************************************************************************/

/**
   @brief Main Loop, I/O
 */
int main()
{

  char *line;
  char **arguments;
  int status;
  int size = 1000;
  char currentfolder[size];

  do
  {
    getcwd(currentfolder, size);
    printf("Group44");
    if (currentfolder != NULL)
      printf("/%s", currentfolder);
    printf("> ");
    line = read_line();
    arguments = tokeniser(line);
    status = execute(arguments);

    free(line);
    free(arguments);
    //free(currentfolder);
    size = 1000;
  } while (status);

  return EXIT_SUCCESS;
}

/*******************************************************************************************************************/