/*
** EPITECH PROJECT, 2023
** cd_command
** File description:
** psu
*/

#include <unistd.h>
#include <malloc.h>
#include "my.h"
#include "mysh.h"

static void set_which_dir(envcpy_t *env2, char **arg)
{
    if (my_strcmp(arg[1], "~") == 0)
        go_home(env2);
    else if (my_strcmp(arg[1], "-") == 0)
        go_previous(env2);
    else
        search_dir(env2, arg);
}

void set_cd(envcpy_t *env2, char **arg)
{
    int argc = 0;

    count_argument(&argc, arg);
    if (argc == 1) {
        go_home(env2);
    } else if (argc == 2) {
        set_which_dir(env2, arg);
    } else {
        my_putstr("cd: Too many arguments.\n");
    }
}
