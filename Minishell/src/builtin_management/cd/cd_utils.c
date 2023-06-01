/*
** EPITECH PROJECT, 2023
** cd_command2
** File description:
** psu
*/

#include <unistd.h>
#include <malloc.h>
#include <dirent.h>
#include <sys/stat.h>
#include "my.h"
#include "mysh.h"

static void replace_env_pwd(envcpy_t *env2, char *new_pwd)
{
    for (int x = 0; x < env2[0].max_size; x += 1) {
        if (my_strcmp(env2[x].term, "PWD") == 0) {
            free(env2[x].def);
            env2[x].def = my_strdup(new_pwd);
        }
    }
}

void go_home(envcpy_t *env2)
{
    char get_home[100];
    int occurence = 0;
    int i = 0;
    char cwd[1024];

    if (env2[0].prev_cwd != NULL)
        free(env2[0].prev_cwd);
    getcwd(cwd, sizeof(cwd));
    while (occurence != 3) {
        get_home[i] = cwd[i];
        if (cwd[i] == '/')
            occurence += 1;
        i += 1;
    }
    get_home[i - 1] = '\0';
    env2[0].prev_cwd = my_strdup(cwd);
    chdir(get_home);
    replace_env_pwd(env2, get_home);
}

void go_previous(envcpy_t *env2)
{
    char cwd[1024];

    if (env2[0].prev_cwd != NULL) {
        getcwd(cwd, sizeof(cwd));
        chdir(env2[0].prev_cwd);
        free(env2[0].prev_cwd);
        env2[0].prev_cwd = my_strdup(cwd);
        getcwd(cwd, sizeof(cwd));
        replace_env_pwd(env2, cwd);
    }
}

void search_dir(envcpy_t *env2, char **arg)
{
    struct stat info;
    char cwd[1024];

    if (stat(arg[1], &info) == -1) {
        my_putstr(arg[1]);
        my_putstr(": No such file or directory.\n");
        return;
    }
    if (S_ISDIR(info.st_mode)) {
        if (env2[0].prev_cwd != NULL)
            free(env2[0].prev_cwd);
        getcwd(cwd, sizeof(cwd));
        env2[0].prev_cwd = my_strdup(cwd);
        chdir(arg[1]);
        getcwd(cwd, sizeof(cwd));
        replace_env_pwd(env2, cwd);
    } else {
        my_putstr(arg[1]);
        my_putstr(": Not a directory.\n");
    }
}
