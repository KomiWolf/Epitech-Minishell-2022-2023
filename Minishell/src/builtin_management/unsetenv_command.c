/*
** EPITECH PROJECT, 2023
** unsetenv_command
** File description:
** psu
*/

#include <malloc.h>
#include "my.h"
#include "mysh.h"

static void move_all(envcpy_t *env2, int x)
{
    for (int z = x; z < env2[0].max_size - 1; z += 1) {
        if (env2[z + 1].term != NULL) {
            env2[z].term = my_strdup(env2[z + 1].term);
            free(env2[z + 1].term);
        }
        if (env2[z + 1].def != NULL) {
            env2[z].def = my_strdup(env2[z + 1].def);
            free(env2[z + 1].def);
        }
    }
}

static void found_in_struct(envcpy_t *env2, char **arg, int *x, int i)
{
    if (my_strcmp(arg[i], env2[*x].term) == 0) {
        free(env2[*x].term);
        if (env2[*x].def != NULL) {
            free(env2[*x].def);
        }
        if (*x != env2[0].max_size - 1)
            move_all(env2, *x);
        env2[0].max_size -= 1;
        *x -= 1;
    }
}

static void set_loop(envcpy_t *env2, char **arg)
{
    for (int i = 1; arg[i] != NULL; i += 1) {
        for (int x = 0; x < env2[0].max_size; x += 1) {
            found_in_struct(env2, arg, &x, i);
        }
    }
}

void set_unsetenv(envcpy_t *env2, char **arg)
{
    int argc = 0;

    count_argument(&argc, arg);
    if (argc == 1)
        my_putstr("unsetenv: Too few arguments.\n");
    else if (argc > 1)
        set_loop(env2, arg);
}
