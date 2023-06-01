/*
** EPITECH PROJECT, 2023
** run_pipe
** File description:
** psu
*/

#include <unistd.h>
#include "mysh.h"
#include "pipe.h"

static void init_pipe(pipe_t *pipe_track)
{
    pipe_track->pid = 0;
    pipe_track->stdin_copy = dup(STDIN_FILENO);
    pipe_track->stdout_copy = dup(STDOUT_FILENO);
    pipe_track->input_fd = STDIN_FILENO;
}

static void free_resources(pipe_t *pipe_track)
{
    dup2(pipe_track->stdin_copy, STDIN_FILENO);
    dup2(pipe_track->stdout_copy, STDOUT_FILENO);
    close(pipe_track->stdin_copy);
    close(pipe_track->stdout_copy);
}

void run_pipe(envcpy_t *env2, separator_t *sep)
{
    pipe_t pipe_track;

    if (pipe_with_builtin(env2, sep) == 1) {
        return;
    }
    init_pipe(&pipe_track);
    set_pipe_loop(env2, sep, &pipe_track);
    free_resources(&pipe_track);
}
