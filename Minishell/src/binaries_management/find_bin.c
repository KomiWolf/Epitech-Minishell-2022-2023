/*
** EPITECH PROJECT, 2023
** find_bin
** File description:
** psu
*/

#include <stdbool.h>
#include <dirent.h>
#include <malloc.h>
#include <sys/stat.h>
#include "my.h"
#include "mysh.h"

static bool read_dir(DIR *box, char **arg)
{
    struct dirent *content = NULL;

    while ((content = readdir(box)) != NULL) {
        if (my_strcmp(content->d_name, arg[0]) == 0) {
            closedir(box);
            return true;
        }
    }
    return false;
}

static char *find_binaries(char **arg, char **path, char *filepath)
{
    DIR *box = NULL;
    int len = (my_strlen(arg[0]) + 2);

    for (int i = 0; path[i] != NULL; i++) {
        box = opendir(path[i]);
        if (box == NULL)
            continue;
        if (read_dir(box, arg) == true) {
            filepath = malloc(sizeof(char) * (my_strlen(path[i]) + len));
            my_strcpy(filepath, path[i]);
            my_strcat(filepath, "/");
            my_strcat(filepath, arg[0]);
            return filepath;
        }
        closedir(box);
    }
    return NULL;
}

static char *when_empty_path(char *filepath)
{
    char *bin_folder = malloc(sizeof(char) * 100);

    my_strcpy(bin_folder, "/bin/");
    my_strcat(bin_folder, filepath);
    free(filepath);
    return bin_folder;
}

static char *if_exist(char *filepath)
{
    struct stat info;

    if (stat(filepath, &info) == 0) {
        return filepath;
    }
    free(filepath);
    return NULL;
}

char *is_found(envcpy_t *env2, char **arg)
{
    char **path = NULL;
    char *filepath = my_strdup(arg[0]);

    for (int i = 0; filepath[i] != '\0'; i += 1) {
        if (filepath[i] == '/')
            return if_exist(filepath);
    }
    path = search_path(env2);
    if (path == NULL)
        return when_empty_path(filepath);
    if (filepath != NULL)
        free(filepath);
    filepath = find_binaries(arg, path, filepath);
    if (filepath == NULL) {
        free_tab(path);
        return NULL;
    }
    free_tab(path);
    return filepath;
}
