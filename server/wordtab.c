/*
** EPITECH PROJECT, 2019
** wordtab
** File description:
** wordtab
*/

#include "wordtab.h"

int wt_free_tab(char **tab)
{
    for (int i = 0; tab && tab[i] != NULL; ++i)
        free(tab[i]);
    tab ? free(tab) : 0;
    return (0);
}

int wt_utils(char *str, char **delims, int mode, int pos)
{
    int index = -1;
    size_t len = 0;

    for (int i = 0; !mode && delims[i]; ++i) {
        if (strncmp(str, delims[i], strlen(delims[i])) == 0) {
            len < strlen(delims[i]) ? index = i : 0;
            len < strlen(delims[i]) ? len = strlen(delims[i]) : 0;
        }
    }
    for (int i = 0; mode == -1 && str[i]; ++i) {
        if (wt_utils(&str[i], delims, 0, 0) >= 0)
            return (i);
    }
    for (int i = 0; mode > 0 && i < mode; ++i) {
        for (int j = pos; str[j]; ++j)
            str[j] = str[j + 1];
    }
    return (index);
}

int wt_count_elems(char *str, char **delims)
{
    int elems = 0;
    int idx = -1;

    for (int i = 0; str[i];) {
        if ((idx = wt_utils(&str[i], delims, 0, 0)) >= 0) {
            elems += 1;
            i += strlen(delims[idx]);
        } else
            i += 1;
    }
    return (elems + 1);
}

char *wt_epur_str(char *str, char **delims, int free_str)
{
    char *res = str && strlen(str) ? strdup(str) : NULL;
    int idx = -1;

    if (!res)
        return (NULL);
    while ((idx = wt_utils(res, delims, 0, 0)) >= 0)
        wt_utils(res, delims, strlen(delims[idx]), 0);
    for (int i = 0; res[i];) {
        if ((idx = wt_utils(&res[i], delims, 0, 0)) >= 0 &&
            (wt_utils(&res[i + 1], delims, 0, 0) >= 0 || !res[i + 1]))
            wt_utils(res, delims, strlen(delims[idx]), i);
        else if ((idx = wt_utils(&res[i], delims, 0, 0)) >= 0 &&
            wt_utils(&res[i + 1], delims, 0, 0) < 0)
            i += strlen(delims[idx]);
        else
            i += 1;
    }
    free_str ? free(str) : 0;
    return (res);
}

char **wordtab(char *str, char **delims)
{
    char **res = NULL;
    char *epur = wt_epur_str(str, delims, 0);
    int elems = epur ? wt_count_elems(epur, delims) : 0;
    int idx = 0;
    int sep_idx = -1;

    if (!epur || !(res = malloc(sizeof(char *) * (elems + 1))))
        return (NULL);
    for (int i = 0; i < elems; ++i) {
        res[i] = strdup(&epur[idx]);
        res[i][(sep_idx = wt_utils(res[i], delims, -1, 0)) >= 0 ?
            (size_t)sep_idx : strlen(res[i])] = 0;
        idx += strlen(res[i]);
        idx += (sep_idx = wt_utils(&epur[idx], delims, 0, 0)) >= 0 ?
            strlen(delims[sep_idx]) : 0;
    }
    res[elems] = NULL;
    free(epur);
    return (res);
}
