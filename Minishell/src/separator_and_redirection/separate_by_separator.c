/*
** EPITECH PROJECT, 2023
** who_to_send
** File description:
** psu
*/

#include <stddef.h>
#include <malloc.h>
#include <stdio.h>
#include "my.h"
#include "mysh.h"

static int count_separator_number(char *arg)
{
    int count = 0;

    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '|' || arg[i] == '>' || arg[i] == '<' ||
        (arg[i] == '<' && arg[i + 1] == '<') ||
        (arg[i] == '>' && arg[i + 1] == '>'))
            count += 1;
    }
    return count + 1;
}

static void fill_command(char *arg, separator_t *sep, int *j, int k)
{
    int x = 0;

    sep[k].command = malloc(sizeof(char) * my_strlen(arg) + 1);
    while (arg[*j] != '\0') {
        if (arg[*j] == '|' || arg[*j] == '<' || arg[*j] == '>') {
            break;
        }
        sep[k].command[x] = arg[*j];
        x++;
        (*j)++;
    }
    sep[k].command[x] = '\0';
}

static void fill_separator(char *arg, separator_t *sep, int *j, int k)
{
    int x = 0;

    sep[k].separator = malloc(sizeof(char) * my_strlen(arg) + 1);
    while (arg[*j] == '|' || arg[*j] == '>' || arg[*j] == '<') {
        sep[k].separator[x] = arg[*j];
        x++;
        (*j)++;
    }
    sep[k].separator[x] = '\0';
}

static void set_loop_to_fill_struct(char *arg, separator_t *sep, int *k)
{
    int i = 0;
    int j = 0;

    while (arg[i] != '\0') {
        fill_command(arg, sep, &j, *k);
        i = j;
        if (arg[i] == '\0') {
            sep[*k].separator = NULL;
            break;
        }
        fill_separator(arg, sep, &j, *k);
        sep[*k].is_pipe = false;
        if (my_strcmp(sep[(*k)].separator, "|") == 0) {
            sep[*k].is_pipe = true;
        }
        *k += 1;
    }
}

void separate_inside_of_command(envcpy_t *env2, char *cmd)
{
    int count = count_separator_number(cmd);
    separator_t *sep = NULL;
    int k = 0;

    sep = malloc(sizeof(separator_t) * (count + 1));
    set_loop_to_fill_struct(cmd, sep, &k);
    free(cmd);
    sep[0].max_size = k;
    who_to_send_to(env2, sep);
    free_struct(NULL, sep);
}
