/*
** EPITECH PROJECT, 2023
** fill_struct
** File description:
** psu
*/

#include <stddef.h>
#include "my.h"
#include "mysh.h"

void fill_struct(char **env, envcpy_t *env2)
{
    char **tmp = NULL;
    int i = 0;

    for (i = 0; env[i] != NULL; i++) {
        if (env[i] != NULL)
            tmp = my_env_to_word_array(env[i]);
        if (tmp[0] != NULL)
            env2[i].term = my_strdup(tmp[0]);
        if (tmp[1] != NULL)
            env2[i].def = my_strdup(tmp[1]);
        else
            env2[i].def = NULL;
        free_tab(tmp);
    }
    env2[0].max_size = i;
    env2[0].prev_cwd = NULL;
}
