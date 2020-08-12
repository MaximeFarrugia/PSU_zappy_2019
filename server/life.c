/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** life
*/

#include "server.h"

void eat_to_survive(server_t *server, client_t *client)
{
    if (client->inv[0] > 0)
        --client->inv[0];
    else {
        dprintf(client->fd, "dead\n");
        logout_cmd(server, client, NULL, NULL);
    }
}

void life_manager(server_t *server)
{
    client_t *client = NULL;
    double waiting;

    STAILQ_FOREACH(client, &server->clients, next) {
        if (client->fd < 0 || client->graphical || !client->team)
            continue;
        waiting = (double)(clock() - client->life) / CLOCKS_PER_SEC;
        if (waiting >= ((double)(UNITS_OF_TIME / server->freq))) {
            eat_to_survive(server, client);
            client->life = clock();
        }
    }
}
