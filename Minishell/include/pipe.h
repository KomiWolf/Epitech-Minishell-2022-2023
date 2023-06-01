/*
** EPITECH PROJECT, 2023
** pipe.h
** File description:
** psu
*/

#ifndef PIPE_H_
    #define PIPE_H_

    #include <sys/types.h>
    #include "mysh.h"

typedef struct pipe_s {
    pid_t pid;
    int pipe_fd[2];
    int stdout_copy;
    int stdin_copy;
    int input_fd;
} pipe_t;

void set_pipe_loop(envcpy_t *env2, separator_t *sep, pipe_t *pipe_t);
int pipe_with_builtin(envcpy_t *env2, separator_t *sep);

#endif
