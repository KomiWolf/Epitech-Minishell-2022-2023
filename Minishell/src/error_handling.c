/*
** EPITECH PROJECT, 2023
** error_handling.c
** File description:
** psu
*/

#include "../include/my.h"

int wrong_number_arg(int ac)
{
    if (ac > 1) {
        my_putstr("Error: Wrong argument\n");
        return 84;
    }
    return 0;
}
