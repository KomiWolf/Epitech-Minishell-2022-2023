/*
** EPITECH PROJECT, 2023
** simple_pipe
** File description:
** psu
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mysh.h"
#include "pipe.h"

static void manage_child(tracker_t *t, envcpy_t *e, pipe_t *p, separator_t *s)
{
    close(p->pipe_fd[0]);
    if (dup2(p->pipe_fd[1], STDOUT_FILENO) == -1)
        exit(EXIT_FAILURE);
    init_tracker(t, s[0].command, true);
    separate_argument(e, t, NULL);
    close(p->pipe_fd[1]);
    exit(EXIT_SUCCESS);
}

void run_simple_pipe(envcpy_t *env2, separator_t *sep, int i)
{
    pipe_t pipe_tracker;
    tracker_t tracker;

    pipe(pipe_tracker.pipe_fd);
    pipe_tracker.pid = fork();
    if (pipe_tracker.pid == 0) {
        manage_child(&tracker, env2, &pipe_tracker, sep);
    } else {
        close(pipe_tracker.pipe_fd[1]);
        if (dup2(pipe_tracker.pipe_fd[0], STDIN_FILENO) == -1)
            return;
        init_tracker(&tracker, sep[i + 1].command, false);
        separate_argument(env2, &tracker, NULL);
        close(pipe_tracker.pipe_fd[0]);
        waitpid(pipe_tracker.pid, NULL, 0);
    }
}
