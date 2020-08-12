/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** setup_player
*/

#include "server.h"

void setup_player(server_t *server, client_t *client, team_t *team)
{
    static int id = 1;

    team->players += 1;
    client->id = id++;
    client->team = strdup(team->name);
    client->x = rand() % server->map.w;
    client->y = rand() % server->map.h;
    client->orientation = rand() % 4 + 1;
    client->life = clock();
    client->inv[0] = 10;
    client->incantation_status = false;
    broadcast_graphicals(server, "pnw %d %d %d %d %d %s\n", client->id,
        client->x, client->y, (int)client->orientation, client->level,
        client->team);
    dprintf(client->fd, "%d\n", team->max_players - team->players);
    dprintf(client->fd, "%d %d\n", server->map.w, server->map.h);
    server->map.tiles[client->y][client->x].players += 1;
    broadcast_graphicals_func(server, mct_cmd, NULL, NULL);
}

void try_join_as_egg(server_t *server, client_t *client, team_t *team)
{
    egg_t *egg = NULL;
    client_t *cl = NULL;

    STAILQ_FOREACH(egg, &server->eggs, next) {
        if (!egg->hatched)
            continue;
        cl = get_client_from_id(&server->clients, egg->client_id);
        if (!strcasecmp(cl->team, team->name))
            continue;
        broadcast_graphicals(server, "ebo %d\n", egg->nb);
        STAILQ_REMOVE(&server->eggs, egg, egg_s, next);
        setup_player(server, client, team);
    }
}

void try_join_team(server_t *server, client_t *client, char **cmd)
{
    team_t *team = NULL;

    STAILQ_FOREACH(team, &server->teams, next) {
        if (!strcasecmp(team->name, cmd[0]) &&
            team->players < team->max_players) {
            try_join_as_egg(server, client, team);
            setup_player(server, client, team);
            return;
        }
    }
    dprintf(client->fd, "ko\n");
}
