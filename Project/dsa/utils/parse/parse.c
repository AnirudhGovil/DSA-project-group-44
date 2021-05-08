#include "parse.h"

// Split cmd into array of parameters
void parse(char *cmd, char **params, char *use_string)
{
    if (cmd[strlen(cmd) - 1] == '\n')
        cmd[strlen(cmd) - 1] = '\0';

    //Remove leading whitespace
    char *p = cmd;
    int l = strlen(cmd);
    while (isspace(p[l - 1]))
        p[--l] = 0;
    while (*p && isspace(*p))
        ++p, --l;
    memmove(cmd, p, l + 1);

    //Remove extra whitespace characters
    int i, x;
    for (i = x = 0; cmd[i]; ++i)
        if (!isspace(cmd[i]) || (i > 0 && !isspace(cmd[i - 1])))
            cmd[x++] = cmd[i];
    cmd[x] = '\0';

    //tokeniser stores parameters in params[i]
    for (int i = 0; i < 100; i++)
    {
        params[i] = strsep(&cmd, " ");
        if (params[i] == NULL)
            break;
    }

    //ls function
    if (strcmp(params[0], "ls") == 0)
        strcat(params[1], ".");

    //use function
    if (!params[1])
    {
        params[1] = (char *)malloc(sizeof(char) * 10001);
        strcpy(params[1], use_string);
    }
}