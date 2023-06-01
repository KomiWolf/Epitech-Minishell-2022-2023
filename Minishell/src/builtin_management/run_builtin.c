/*
** EPITECH PROJECT, 2023
** run_builtin
** File description:
** psu
*/

#include <stdlib.h>
#include "my.h"
#include "mysh.h"

static int run_builtin_ovf2(envcpy_t *env2, char **arg)
{
    if (my_strcmp(arg[0], "unsetenv") == 0) {
        set_unsetenv(env2, arg);
        return 0;
    }
    if (my_strcmp(arg[0], "cd") == 0) {
        set_cd(env2, arg);
        return 0;
    }
    if (my_strcmp(arg[0], "clear") == 0) {
        my_putstr("\033[2J\033[H");
        return 0;
    }
    if (my_strcmp(arg[0], "date") == 0) {
        my_putstr("Tue Jan 19 03:14:07 AM UTC 2038");
        return 0;
    }
    return 84;
}

int run_builtin(envcpy_t *env2, char **arg)
{
    if (my_strcmp(arg[0], "env") == 0) {
        set_env(env2, arg);
        return 0;
    }
    if (my_strcmp(arg[0], "printenv") == 0) {
        set_printenv(env2, arg);
        return 0;
    }
    if (my_strcmp(arg[0], "setenv") == 0) {
        set_setenv(env2, arg);
        return 0;
    }
    if (run_builtin_ovf2(env2, arg) == 0)
        return 0;
    return 84;
}
