/*
** EPITECH PROJECT, 2023
** pipe_and_redirect_utils
** File description:
** psu
*/

#include "mysh.h"

void fill_filepath(separator_t *sep, char *filepath, int i)
{
    int k = 0;

    for (int j = 0; sep[i].command[j] != '\0'; j++) {
        if (sep[i].command[j] == ' ' || sep[i].command[j] == '\t' ||
        sep[i].command[j] == '\n')
            continue;
        filepath[k] = sep[i].command[j];
        k++;
    }
    filepath[k] = '\0';
}
