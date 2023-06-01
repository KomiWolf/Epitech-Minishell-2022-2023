/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

int my_strlen(char const *str);
int my_putstr(char const *str);
void my_putchar(char c);
char **my_env_to_word_array(char *str);
char **my_path_to_word_array(char *str);
int my_strcmp(char const *s1, char const *s2);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
char *my_strcat(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);

#endif
