/*
** EPITECH PROJECT, 2023
** setenv_command
** File description:
** psu
*/

#include <stddef.h>
#include <malloc.h>
#include <stdbool.h>
#include "my.h"
#include "mysh.h"

static void is_correct_arg_number(char **arg)
{
    my_putstr(arg[0]);
    my_putstr(": Too many argument.\n");
}

static void replace_if_exist(envcpy_t *env2, int argc, char **arg, int i)
{
    if (argc == 2) {
        if (env2[i].def != NULL)
            free(env2[i].def);
        env2[i].def = NULL;
    }
    if (argc == 3) {
        if (env2[i].def != NULL)
            free(env2[i].def);
        env2[i].def = my_strdup(arg[2]);
    }
}

static void add_variable(envcpy_t *env2, int argc, char **arg)
{
    int max = env2[0].max_size;

    for (int i = 0; i < max; i += 1) {
        if (my_strcmp(env2[i].term, arg[1]) == 0) {
            replace_if_exist(env2, argc, arg, i);
            return;
        }
    }
    env2[0].max_size += 1;
    max = env2[0].max_size;
    if (argc == 2) {
        env2[max - 1].term = my_strdup(arg[1]);
        env2[max - 1].def = NULL;
    }
    if (argc == 3) {
        env2[max - 1].term = my_strdup(arg[1]);
        env2[max - 1].def = my_strdup(arg[2]);
    }
}

static bool is_wrong_character(char **arg)
{
    if ((arg[1][0] < 'A' || arg[1][0] > 'Z') &&
    (arg[1][0] < 'a' || arg[1][0] > 'z') && arg[1][0] != '_') {
        my_putstr(arg[0]);
        my_putstr(": Variable name must begin with a letter.\n");
        return true;
    }
    for (int j = 1; arg[1][j] != '\0'; j += 1) {
        if ((arg[1][j] < 'A' || arg[1][j] > 'Z') &&
        (arg[1][j] < 'a' || arg[1][j] > 'z') && arg[1][j] != '_' &&
        (arg[1][j] < '0' || arg[1][j] > '9')) {
            my_putstr(arg[0]);
            my_putstr(": Variable name must contain ");
            my_putstr("alphanumeric characters.\n");
            return true;
        }
    }
    return false;
}

void set_setenv(envcpy_t *env2, char **arg)
{
    int argc = 0;

    count_argument(&argc, arg);
    if (argc == 1) {
        print_env(env2);
        return;
    }
    if (argc == 2 || argc == 3) {
        if (is_wrong_character(arg) == true)
            return;
    }
    if (argc > 3) {
        is_correct_arg_number(arg);
        return;
    }
    add_variable(env2, argc, arg);
}
