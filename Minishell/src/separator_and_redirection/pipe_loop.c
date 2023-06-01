/*
** EPITECH PROJECT, 2023
** pipe_loop
** File description:
** psu
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "my.h"
#include "pipe.h"

static void count_pipe(tracker_t *tracker, separator_t *sep)
{
    tracker->pipe_count = 0;
    for (int j = 0; sep[j].separator != NULL; j++) {
        if (my_strcmp(sep[j].separator, "|") == 0)
            tracker->pipe_count++;
    }
}

static void set_parent(pipe_t *pipe_t, tracker_t *tracker)
{
    close(pipe_t->pipe_fd[1]);
    pipe_t->input_fd = pipe_t->pipe_fd[0];
    waitpid(pipe_t->pid, NULL, 0);
}

static void setup_child(pipe_t *p, tracker_t *tracker, separator_t *sep, int i)
{
    close(p->pipe_fd[0]);
    dup2(p->input_fd, STDIN_FILENO);
    if (i < tracker->pipe_count) {
        dup2(p->pipe_fd[1], STDOUT_FILENO);
    }
    close(p->pipe_fd[1]);
    init_tracker(tracker, sep[i].command, false);
    close(p->pipe_fd[0]);

}

static void launch_child(tracker_t *t, separator_t *sep, pipe_t *p, envcpy_t *e)
{
    dup2(p->pipe_fd[1], STDOUT_FILENO);
    separate_argument(e, t, NULL);
    dup2(p->stdout_copy, STDOUT_FILENO);
    close(p->stdin_copy);
    close(p->stdout_copy);
    close(p->pipe_fd[1]);
    free_struct(e, sep);
}

void set_pipe_loop(envcpy_t *env2, separator_t *sep, pipe_t *p)
{
    tracker_t tracker;

    count_pipe(&tracker, sep);
    if (tracker.pipe_count == 1) {
        run_simple_pipe(env2, sep, 0);
        return;
    }
    for (int i = 0; i <= tracker.pipe_count; i++) {
        if (pipe(p->pipe_fd) == -1)
            break;
        p->pid = fork();
        if (p->pid == 0) {
            setup_child(p, &tracker, sep, i);
            launch_child(&tracker, sep, p, env2);
            exit(tracker.status);
        } else {
            set_parent(p, &tracker);
        }
    }
}
