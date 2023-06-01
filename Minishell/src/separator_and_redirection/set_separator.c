/*
** EPITECH PROJECT, 2023
** run_redirection
** File description:
** psu
*/

#include <malloc.h>
#include <string.h>
#include "my.h"
#include "mysh.h"

static int count_size(char *cmd)
{
    int total = 0;

    for (int i = 0; cmd[i] != '\0'; i += 1) {
        if (cmd[i] == '|' || cmd[i] == ';' ||
        cmd[i] == '<' || cmd[i] == '>' ||
        (cmd[i] == '<' && cmd[i + 1] == '<') ||
        (cmd[i] == '>' && cmd[i + 1] == '>'))
            total += 1;
    }
    return total + 1;
}

static bool if_redirection_exist(char **sep_arg, int i)
{
    for (int j = 0; sep_arg[i][j] != '\0'; j++) {
        if (sep_arg[i][j] == '|' || sep_arg[i][j] == '<' ||
        sep_arg[i][j] == '>') {
            return true;
        }
    }
    return false;
}

void set_separator(envcpy_t *env2, char *cmd)
{
    tracker_t tracker;
    char **sep_arg = NULL;

    if (check_pipe_and_redirection(cmd) == false) {
        return;
    }
    sep_arg = malloc(sizeof(char *) * (count_size(cmd) + 3));
    fill_in_tab(sep_arg, cmd, ";", true);
    for (int i = 0; sep_arg[i] != NULL; i++) {
        if (if_redirection_exist(sep_arg, i) == true) {
            separate_inside_of_command(env2, sep_arg[i]);
        } else {
            init_tracker(&tracker, sep_arg[i], false);
            separate_argument(env2, &tracker, NULL);
        }
    }
    free(sep_arg);
}
