/*
** EPITECH PROJECT, 2023
** shell_utils
** File description:
** psu
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "mysh.h"

static void fill_with_space_at_end(char **tab, char *tmp, int i)
{
    int j = 0;

    tab[i] = malloc(sizeof(char) * my_strlen(tmp) + 3);
    for (j = 0; tmp[j] != '\0' && tmp[j] != '\n'; j++) {
        tab[i][j] = tmp[j];
    }
    tab[i][j] = ' ';
    tab[i][j + 1] = '\0';
}

void fill_in_tab(char **tab, char *command, char *sep, bool is_redirect)
{
    char *tmp = NULL;
    int i = 0;

    tmp = strtok(command, sep);
    while (tmp != NULL) {
        if (tmp != NULL && is_redirect == false) {
            tab[i] = my_strdup(tmp);
        }
        if (tmp != NULL && is_redirect == true) {
            fill_with_space_at_end(tab, tmp, i);
        }
        tmp = strtok(NULL, sep);
        i += 1;
    }
    tab[i] = NULL;
}

void init_tracker(tracker_t *tracker, char *cmd, bool boolean)
{
    tracker->command = my_strdup(cmd);
    tracker->is_pipe = boolean;
    tracker->separated_command = NULL;
    tracker->status = 0;
    tracker->sep_arg = NULL;
}

void free_tab(char **tab)
{
    int i = 0;

    while (tab[i] != NULL) {
        if (tab[i] != NULL)
            free(tab[i]);
        i += 1;
    }
    free(tab);
}

void free_struct(envcpy_t *env, separator_t *sep)
{
    if (sep != NULL) {
        for (int i = 0; i <= sep[0].max_size; i++)
            free(sep[i].command);
        for (int i = 0; i < sep[0].max_size; i++)
            free(sep[i].separator);
        free(sep);
    }
    if (env == NULL)
        return;
    for (int i = 0; i < env[0].max_size; i += 1) {
        if (env[i].term == NULL)
            continue;
        free(env[i].term);
        if (env[i].def == NULL)
            continue;
        free(env[i].def);
    }
    free(env);
}
