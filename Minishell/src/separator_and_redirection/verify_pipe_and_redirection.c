/*
** EPITECH PROJECT, 2023
** verify_after_pipe
** File description:
** psu
*/

#include <stdbool.h>
#include "my.h"

static bool verify_after_pipe(char *cmd)
{
    int i = 0;
    bool has_char = false;

    for (i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == '|')
            break;
    }
    if (cmd[i] == '\0')
        return true;
    for (int j = i + 1; cmd[j] != '\0'; j++) {
        if (cmd[j] == '|')
            has_char = false;
        if (cmd[j] != '|' && cmd[j] != '<' && cmd[j] != '>' && cmd[j] != ' ' &&
        cmd[j] != '\t' && cmd[j] != '\n')
            has_char = true;
    }
    return has_char;
}

static bool verify_redirection(char *cmd)
{
    int i = 0;
    bool has_char = 0;

    for (i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == '<' || cmd[i] == '>')
            break;
    }
    if (cmd[i] == '\0')
        return true;
    if (cmd[i + 1] == '<' || cmd[i + 1] == '>')
        i++;
    for (int j = i + 1; cmd[j] != '\0'; j++) {
        if (cmd[j] == '<' || cmd[j] == '>' || cmd[j] == '|')
            break;
        if (cmd[j] != '|' && cmd[j] != '<' && cmd[j] != '>' && cmd[j] != ' ' &&
        cmd[j] != '\t' && cmd[j] != '\n')
            has_char = true;
    }
    return has_char;
}

bool check_pipe_and_redirection(char *cmd)
{
    if (verify_after_pipe(cmd) == false) {
        my_putstr("Invalid null command.\n");
        return false;
    }
    if (verify_redirection(cmd) == false) {
        my_putstr("Missing name for redirect.\n");
        return false;
    }
    return true;
}
