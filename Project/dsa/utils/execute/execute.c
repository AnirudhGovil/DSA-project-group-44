#include "execute.h"

// execute the commands
int execute(char **params, char*commands_str[], int (*commands_func[])(char **))
{
    // Fork process
    pid_t pid = fork();

    // Error in forking
    if (pid < 0)
    {
        char *error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }

    // Check if the child process was created successfully
    else if (pid == 0)
    {
        //exit function
        if (strcmp(params[0], "exit") == 0)
            kill(0, SIGTERM);

        //check if it is a custom command and execute it
        for (int i = 0; i < 8; i++)
        {
            if (strcmp(params[0], commands_str[i]) == 0)
            {
                return (*commands_func[i])(params);
            }
        }

        // Execute built-in command
        if (execvp(params[0], params) < 0)
        {
            printf("Command not found: %s\n", params[0]);
            return 1;
        }

        // Error occurred in executing commmand
        char *error = strerror(errno);
        printf("Shell: %s: %s\n", params[0], error);
        return 1;
    }

    // Parent process
    else
    {
        // Wait for child process to finish
        int childStatus;
        waitpid(pid, &childStatus, 0);
        return 1;
    }
}
