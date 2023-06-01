/*
** EPITECH PROJECT, 2023
** run_left_redirect
** File description:
** psu
*/

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include "my.h"
#include "mysh.h"

static int open_failed(int fd, char *filepath)
{
    if (fd == -1) {
        my_putstr(filepath);
        my_putstr(": No such file or directory.\n");
        free(filepath);
        return 84;
    }
    return 0;
}

void single_left_redirect(envcpy_t *env2, separator_t *sep, int i)
{
    tracker_t tracker;
    char *filepath = malloc(sizeof(char) * my_strlen(sep[i + 1].command) + 1);
    int fd = 0;
    int stdin_copy = 0;

    fill_filepath(sep, filepath, i + 1);
    fd = open(filepath, O_RDONLY);
    if (open_failed(fd, filepath) == 84) {
        return;
    }
    init_tracker(&tracker, sep[i].command, false);
    stdin_copy = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    separate_argument(env2, &tracker, sep);
    dup2(stdin_copy, STDIN_FILENO);
    close(stdin_copy);
    close(fd);
    free(filepath);
}
