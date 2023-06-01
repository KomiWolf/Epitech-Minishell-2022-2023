/*
** EPITECH PROJECT, 2023
** path_handling
** File description:
** psu
*/

#include <stddef.h>
#include <malloc.h>
#include "my.h"
#include "mysh.h"

static char **set_path(envcpy_t *env2, int i)
{
    char **path = NULL;

    if (my_strcmp(env2[i].term, "PATH") == 0) {
        if (env2[i].def != NULL) {
            path = my_path_to_word_array(env2[i].def);
            return path;
        } else {
            path = malloc(sizeof(char *) * 2);
            path[0] = my_strdup("a:b");
            path[1] = NULL;
            return path;
        }
    }
    return NULL;
}

char **search_path(envcpy_t *env2)
{
    char **path = NULL;

    for (int i = 0; i < env2[0].max_size; i += 1) {
        path = set_path(env2, i);
        if (path != NULL)
            return path;
    }
    return NULL;
}
