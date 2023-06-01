/*
** EPITECH PROJECT, 2023
** separate_argument
** File description:
** psu
*/

#include <string.h>
#include <malloc.h>
#include "my.h"
#include "mysh.h"

static int count_tab(char *cmd)
{
    int count_tab_height = 0;

    for (int j = 0; cmd[j] != '\0'; j += 1) {
        if ((cmd[j] == ' ' || cmd[j] == '\t') || cmd[j] == '\n')
            count_tab_height += 1;
    }
    return count_tab_height;
}

static void launch_command(envcpy_t *env2, tracker_t *tracker, separator_t *sep)
{
    if (my_strncmp(tracker->separated_command[0], "/bin/env", 8) == 0 ||
    my_strncmp(tracker->separated_command[0], "usr/bin/env", 11) == 0) {
        set_env(env2, tracker->separated_command);
        return;
    }
    if (run_builtin(env2, tracker->separated_command) == 84) {
        if (my_exec(env2, tracker, sep) == 1)
            return;
    }
}

static void replace_char(char *temp)
{
    for (int j = 0; temp[j] != '\0'; j += 1) {
        if (temp[j] == ' ' || temp[j] == '\t')
            temp[j] = '\n';
    }
}

void separate_argument(envcpy_t *env2, tracker_t *tracker, separator_t *sep)
{
    bool character_is_printable = false;
    int count = count_tab(tracker->command) + 3;

    for (int i = 0; tracker->command[i] != '\0'; i += 1) {
        if (tracker->command[i] != ' ' && tracker->command[i] != '\t' &&
        tracker->command[i] != '\n')
            character_is_printable = true;
    }
    if (character_is_printable == false)
        return;
    tracker->separated_command = malloc(sizeof(char *) * count);
    replace_char(tracker->command);
    fill_in_tab(tracker->separated_command, tracker->command, "\n", false);
    launch_command(env2, tracker, sep);
    free(tracker->command);
    free_tab(tracker->separated_command);
}
