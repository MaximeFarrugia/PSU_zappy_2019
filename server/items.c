/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** items
*/

#include "server.h"

int item_to_idx(char *item)
{
    char items[7][10] = { "food", "linemate", "deraumere", "sibur", "mendiane",
        "phiras", "thystame" };

    if (!item)
        return (-1);
    for (int i = 0; i < 7; ++i) {
        if (!strcasecmp(item, items[i]))
            return (i);
    }
    return (-1);
}