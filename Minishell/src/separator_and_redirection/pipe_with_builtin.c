/*
** EPITECH PROJECT, 2023
** pipe_with_builtin
** File description:
** psu
*/

#include <stdlib.h>
#include "my.h"
#include "mysh.h"

static char *copy_str(separator_t *sep, int i)
{
    int k = 0;
    char *command = malloc(sizeof(char) * my_strlen(sep[i].command) + 1);

    for (int j = 0; sep[i].command[j] != '\0'; j++) {
        if (sep[i].command[j] == ' ' || sep[i].command[j] == '\t' ||
        sep[i].command[j] == '\n')
            continue;
        command[k] = sep[i].command[j];
        k++;
    }
    command[k] = '\0';
    return command;
}

int pipe_with_builtin(envcpy_t *env2, separator_t *sep)
{
    int i = 0;
    tracker_t tracker;
    char *command = NULL;

    for (i = 0; sep[i].separator != NULL; i++);
    command = copy_str(sep, i);
    if (my_strncmp(command, "cd", 2) == 0 ||
    my_strncmp(command, "env", 3) == 0 ||
    my_strncmp(command, "setenv", 6) == 0 ||
    my_strncmp(command, "unsetenv", 8) == 0) {
        init_tracker(&tracker, sep[i].command, false);
        separate_argument(env2, &tracker, sep);
        free(command);
        return 1;
    }
    free(command);
    return 0;
}
