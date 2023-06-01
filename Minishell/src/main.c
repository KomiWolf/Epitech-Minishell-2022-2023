/*
** EPITECH PROJECT, 2023
** main
** File description:
** psu
*/

#include <stdlib.h>
#include "my.h"
#include "mysh.h"

int main(int ac, char **av, char **env)
{
    envcpy_t *env2 = NULL;

    (void)av;
    if (wrong_number_arg(ac) == 84)
        return 84;
    env2 = malloc(sizeof(envcpy_t) * 1000);
    if (env2 == NULL)
        return 84;
    fill_struct(env, env2);
    set_prompt_loop(env2);
    return 0;
}
