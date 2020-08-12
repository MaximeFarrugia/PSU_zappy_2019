/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** check_incantation
*/

#include "server.h"

void check_winners(server_t *server, client_t *client)
{
    client_t *tmp = NULL;
    int total = 0;

    STAILQ_FOREACH(tmp, &server->clients, next) {
        if (tmp->fd < 0 || tmp->graphical || !tmp->team)
            continue;
        if (!strcmp(tmp->team, client->team) && tmp->level == 8) {
            total += 1;
        }
    }
    if (total >= 6)
        server->winners = strdup(client->team);
}

void start_incantation(server_t *server, client_t *client)
{
    if (client->graphical) {
        dprintf(client->fd, "suc\n");
        return;
    }
    if (check_stuff(server, client) && check_players(server, client)) {
        execute_incantation(server, client);
        delete_items(server, client);
        check_winners(server, client);
    } else {
        dprintf(client->fd, "ko\n");
    }
}