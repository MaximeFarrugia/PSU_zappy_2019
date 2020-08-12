/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** eggs
*/

#include "server.h"

egg_t *new_egg(int nb, int id)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (!egg)
        return (NULL);
    egg->nb = nb;
    egg->client_id = id;
    egg->hatching = clock();
    egg->hatched = false;
    return (egg);
}

void authorize_new_client(server_t *server, egg_t *egg)
{
    client_t *client = get_client_from_id(&server->clients, egg->client_id);
    team_t *team = get_team_from_name(&server->teams, client->team);

    team->max_players += 1;
    STAILQ_FOREACH(client, &server->clients, next) {
        if (egg->client_id == client->id)
            broadcast_graphicals(server, "eht %d\n", egg->nb);
    }
}

void eggs_manager(server_t *server)
{
    egg_t *egg = NULL;
    double hatching;

    STAILQ_FOREACH(egg, &server->eggs, next) {
        hatching = (double)(clock() - egg->hatching) / CLOCKS_PER_SEC;
        if (hatching >= ((double)( HATCHING_CYCLE / server->freq)) &&
            !egg->hatched) {
            authorize_new_client(server, egg);
            egg->hatched = true;
        }
    }
}