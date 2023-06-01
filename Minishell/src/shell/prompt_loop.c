/*
** EPITECH PROJECT, 2023
** prompt_loop
** File description:
** psu
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "my.h"
#include "mysh.h"

static void leave_prompt(envcpy_t *env2, char *cmd, ssize_t s, separator_t *sep)
{
    if ((s == -1 || my_strcmp(cmd, "exit\n") == 0) &&
        isatty(STDIN_FILENO)) {
        my_putstr("exit\n");
        if (env2[0].prev_cwd != NULL)
            free(env2[0].prev_cwd);
        if (env2 != NULL)
            free_struct(env2, sep);
        if (cmd != NULL)
            free(cmd);
        exit(EXIT_SUCCESS);
    }
}

static bool check_redirection(char *command)
{
    if (command == NULL)
        return false;
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '|' || command[i] == ';' ||
        command[i] == '<' || command[i] == '>')
            return true;
    }
    return false;
}

void launch_execution(envcpy_t *env2, ssize_t stock, char *cmd)
{
    tracker_t tracker;

    if (stock != 1 && check_redirection(cmd) == false) {
        init_tracker(&tracker, cmd, false);
        separate_argument(env2, &tracker, NULL);
    } else if (stock != 1 && check_redirection(cmd) == true) {
        set_separator(env2, cmd);
    }
}

void set_prompt_loop(envcpy_t *env2)
{
    char *cmd = NULL;
    size_t n = 0;
    ssize_t stock = 0;

    while (stock != -1) {
        if (isatty(STDIN_FILENO))
            my_putstr("[my_prompt]$ ");
        stock = getline(&cmd, &n, stdin);
        if (stock == 1)
            continue;
        leave_prompt(env2, cmd, stock, NULL);
        launch_execution(env2, stock, cmd);
    }
}
