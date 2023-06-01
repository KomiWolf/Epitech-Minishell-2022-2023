/*
** EPITECH PROJECT, 2022
** my_strncpy
** File description:
** strncpy
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int a = 0;

    for (; a < n; a++) {
        if (src[a] == '\0')
            break;
        dest[a] = src[a];
    }
    dest[a] = '\0';
    return dest;
}
