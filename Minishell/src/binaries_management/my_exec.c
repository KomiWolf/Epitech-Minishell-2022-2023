/*
** EPITECH PROJECT, 2023
** my_exec
** File description:
** psu
*/

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include "my.h"
#include "mysh.h"

static int put_error(char **arg)
{
    my_putstr(arg[0]);
    my_putstr(": Command not found.\n");
    return 1;
}

static int execute_cmd(envcpy_t *env2, char *f, tracker_t *t, separator_t *sep)
{
    errno = 0;
    if (execve(f, t->separated_command, NULL) == -1) {
        if (errno == EACCES) {
            my_putstr(f);
            my_putstr(": Permission denied.\n");
        } else {
            my_putstr(f);
            my_putstr(": Exec format error. Wrong Architecture.\n");
        }
        if (t->sep_arg != NULL)
            free_tab(t->sep_arg);
        free_struct(env2, sep);
        free(t->command);
        free_tab(t->separated_command);
        free(f);
        return 84;
    }
    return 0;
}

static void set_parent_process(pid_t pid, int status, tracker_t *tracker)
{
    char *put_error = NULL;
    int exit_status = 0;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status) == true) {
        exit_status = WEXITSTATUS(status);
        tracker->status = exit_status;
    }
    if (WIFSIGNALED(status) == true) {
        put_error = strsignal(WTERMSIG(status));
        my_putstr(put_error);
        my_putchar('\n');
    }
}

int my_exec(envcpy_t *env2, tracker_t *tracker, separator_t *sep)
{
    pid_t pid = 0;
    int status = 0;
    char *file = is_found(env2, tracker->separated_command);

    if (file == NULL)
        return put_error(tracker->separated_command);
    if (tracker->is_pipe == false)
        pid = fork();
    if (pid == 0) {
        if (execute_cmd(env2 , file, tracker, sep) == 84)
            exit(EXIT_FAILURE);
    } else if (pid == -1) {
        my_putstr("Error: Fork failed.\n");
    } else {
        set_parent_process(pid, status, tracker);
    }
    free(file);
    return 0;
}
