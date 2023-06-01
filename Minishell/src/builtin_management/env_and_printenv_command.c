/*
** EPITECH PROJECT, 2023
** get_env
** File description:
** psu
*/

#include <stddef.h>
#include "my.h"
#include "mysh.h"

static int print_env_error(char **arg)
{
    int j = 0;

    my_putstr(arg[0]);
    my_putstr(": '");
    while (arg[1][j] != '\0') {
        my_putchar(arg[1][j]);
        j++;
    }
    my_putstr("': ");
    my_putstr("No such file or directory\n");
    return 1;
}

static int print_printenv_error(char **arg)
{
    my_putstr(arg[0]);
    my_putstr(": Too many arguments.\n");
    return 1;
}

int print_env(envcpy_t *env2)
{
    for (int i = 0; i < env2[0].max_size; i += 1) {
        my_putstr(env2[i].term);
        my_putchar('=');
        if (env2[i].def == NULL) {
            my_putchar('\n');
            continue;
        }
        my_putstr(env2[i].def);
        my_putchar('\n');
    }
    return 0;
}

int set_env(envcpy_t *env2, char **arg)
{
    int argc = 0;

    count_argument(&argc, arg);
    if (argc == 1) {
        return print_env(env2);
    } else
        return print_env_error(arg);
    return 0;
}

int set_printenv(envcpy_t *env2, char **arg)
{
    int argc = 0;

    count_argument(&argc, arg);
    if (argc == 1)
        return print_env(env2);
    else if (argc == 2)
        return 0;
    else
        return print_printenv_error(arg);
    return 0;
}
