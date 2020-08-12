/*
** EPITECH PROJECT, 2020
** ai
** File description:
** ai command
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *my_strcat(char *dest, char *src)
{
    int i = 0;
    int j = 0;
    char *str = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));

    if (!str)
        exit(84);
    for (; dest[i] != '\0'; i++)
        str[i] = dest[i];
    for (; src[j] != '\0'; i++, j++)
        str[i] = src[j];
    str[i] = '\0';
    return (str);
}

int main(int ac, char **av)
{
    (void) ac;
    char *cmd = "python3 ia/main.py ";
    for (int i = 1; av[i] != NULL; i++) {
        cmd = my_strcat(cmd, av[i]);
        cmd = my_strcat(cmd, " ");
    }
    system(cmd);
}