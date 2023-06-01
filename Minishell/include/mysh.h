/*
** EPITECH PROJECT, 2023
** mysh.h
** File description:
** psu
*/

#ifndef MYSH_H_
    #define MYSH_H_

    #include <stdbool.h>

typedef struct envcpy_s {
    char *term;
    char *def;
    int max_size;
    char *prev_cwd;
} envcpy_t;

typedef struct tracker_s {
    char *command;
    bool is_pipe;
    char **separated_command;
    char **sep_arg;
    int status;
    int pipe_count;
} tracker_t;

typedef struct separator_s {
    char *command;
    char *separator;
    bool is_pipe;
    int max_size;
} separator_t;

// MAIN
int wrong_number_arg(int ac);

// BUILTIN
void count_argument(int *argc, char **arg);
int set_env(envcpy_t *env2, char **arg);
int set_printenv(envcpy_t *env2, char **arg);
void set_setenv(envcpy_t *env2, char **arg);
int run_builtin(envcpy_t *env2, char **arg);
void put_last(envcpy_t *env2, int argc, char **arg, int i);
int print_env(envcpy_t *env2);
void set_unsetenv(envcpy_t *env2, char **arg);
void set_cd(envcpy_t *env2, char **arg);
void go_home(envcpy_t *env2);
void search_dir(envcpy_t *env2, char **arg);
void go_previous(envcpy_t *env2);

// EXECVE
char *is_found(envcpy_t *env2, char **arg);
int my_exec(envcpy_t *env2, tracker_t *tracker, separator_t *sep);
char **search_path(envcpy_t *env2);

// REDIRECTION
void set_separator(envcpy_t *env2, char *cmd);
void separate_inside_of_command(envcpy_t *env2, char *cmd);
void who_to_send_to(envcpy_t *env2, separator_t *sep);
void run_pipe(envcpy_t *env2, separator_t *sep);
bool check_pipe_and_redirection(char *cmd);
void single_right_redirect(envcpy_t *env2, separator_t *sep, int i);
void double_right_redirect(envcpy_t *env2, separator_t *sep, int i);
void single_left_redirect(envcpy_t *env2, separator_t *sep, int i);
void fill_filepath(separator_t *sep, char *filepath, int i);
void run_simple_pipe(envcpy_t *env2, separator_t *sep, int i);

// SHELL
void separate_argument(envcpy_t *env2, tracker_t *tracker, separator_t *sep);
void set_prompt_loop(envcpy_t *env2);
void fill_struct(char **env, envcpy_t *env2);
void free_struct(envcpy_t *env, separator_t *sep);
void free_tab(char **tab);
char **my_command_to_word_array(char *str);
void fill_in_tab(char **tab, char *command, char *sep, bool is_redirect);
void init_tracker(tracker_t *tracker, char *cmd, bool boolean);

#endif
