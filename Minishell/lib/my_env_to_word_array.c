/*
** EPITECH PROJECT, 2023
** my_str_to_word_array1
** File description:
** cpool
*/

#include <malloc.h>
#include "my.h"

static int count_string_character(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\n' && str[i] != '=')
            count++;
        else
            return count;
    }
    return count;
}

static int count_string_number(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n' || str[i] == '=')
        count++;
    }
    count++;
    return count;
}

static int jump_n(int n, int size, char *str)
{
    int new_n = size + n;

    while (str[new_n] == '\n' || str[new_n] == '\0' ||
    str[new_n] == '=') {
        if (str[new_n] == '\0') {
            return new_n;
        }
        new_n = new_n + 1;
    }
    return new_n;
}

char **my_env_to_word_array(char *str)
{
    int count = count_string_number(str);
    char **tab = malloc(sizeof(char *) * (count + 1));
    int n = 0;
    int line = 0;
    int size = 0;
    char *copy = NULL;

    while (str[n] != '\0' && line < count) {
        size = count_string_character(str + n);
        copy = malloc(sizeof(char) * (size + 1));
        my_strncpy(copy, str + n, size);
        copy[size] = '\0';
        tab[line] = copy;
        line++;
        n = jump_n(n, size, str);
    }
    tab[line] = NULL;
    return tab;
}
