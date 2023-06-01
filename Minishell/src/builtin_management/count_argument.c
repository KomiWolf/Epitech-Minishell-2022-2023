/*
** EPITECH PROJECT, 2023
** count_argument
** File description:
** psu
*/

#include <stddef.h>

void count_argument(int *argc, char **arg)
{
    for (int j = 0; arg[j] != NULL; j++)
        *argc += 1;
}
