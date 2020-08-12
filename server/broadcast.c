/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** broadcast
*/

#include "server.h"

int broadcast_graphicals(server_t *server, const char *fmt, ...)
{
    client_t *client = NULL;
    va_list ap;
    va_list tmp;

    va_start(ap, fmt);
    STAILQ_FOREACH(client, &server->clients, next) {
        va_copy(tmp, ap);
        if (client->graphical)
            vdprintf(client->fd, fmt, tmp);
    }
    va_end(ap);
    va_end(tmp);
    return (0);
}

int broadcast_graphicals_func(server_t *server,
    int (*func)(server_t *, client_t *, char **, void *), char **cmd, void *c2)
{
    client_t *client = NULL;

    STAILQ_FOREACH(client, &server->clients, next) {
        if (client->graphical)
            func(server, client, cmd, c2);
    }
    return (0);
}