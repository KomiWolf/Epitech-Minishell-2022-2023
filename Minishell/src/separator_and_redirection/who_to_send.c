/*
** EPITECH PROJECT, 2023
** who_to_send
** File description:
** psu
*/

#include <stddef.h>
#include "my.h"
#include "mysh.h"

void who_to_send_to(envcpy_t *env2, separator_t *sep)
{
    if (my_strcmp(sep[0].separator, "|") == 0) {
        run_pipe(env2, sep);
    }
    if (my_strcmp(sep[0].separator, ">") == 0) {
        single_right_redirect(env2, sep, 0);
    }
    if (my_strcmp(sep[0].separator, ">>") == 0) {
        double_right_redirect(env2, sep, 0);
    }
    if (my_strcmp(sep[0].separator, "<") == 0) {
        single_left_redirect(env2, sep, 0);
    }
}
