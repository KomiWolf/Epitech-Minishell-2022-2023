/*
** EPITECH PROJECT, 2023
** run_redirect
** File description:
** psu
*/

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include "my.h"
#include "mysh.h"

static void launch_redirect(envcpy_t *e2, tracker_t *t, int fd, separator_t *s)
{
    int stdout_copy = dup(STDOUT_FILENO);

    dup2(fd, STDOUT_FILENO);
    separate_argument(e2, t, s);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdout_copy);
}

void single_right_redirect(envcpy_t *env2, separator_t *sep, int i)
{
    tracker_t tracker;
    char *filepath = malloc(sizeof(char) * my_strlen(sep[i + 1].command) + 1);
    int fd = 0;

    fill_filepath(sep, filepath, i + 1);
    fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        free(filepath);
        return;
    }
    init_tracker(&tracker, sep[i].command, false);
    launch_redirect(env2, &tracker, fd, sep);
    close(fd);
    free(filepath);
}

void double_right_redirect(envcpy_t *env2, separator_t *sep, int i)
{
    tracker_t tracker;
    char *filepath = malloc(sizeof(char) * my_strlen(sep[i + 1].command) + 1);
    int fd = 0;

    fill_filepath(sep, filepath, i + 1);
    fd = open(filepath, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        free(filepath);
        return;
    }
    init_tracker(&tracker, sep[i].command, false);
    launch_redirect(env2, &tracker, fd, sep);
    close(fd);
    free(filepath);
}
