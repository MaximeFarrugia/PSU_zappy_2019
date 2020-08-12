/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** incatation_cmd
*/

#include "server.h"

static const incantation_t incantation[7] = {
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1}
};

void delete_items(server_t *server, client_t *client)
{
    for (int i = 0; i < incantation[client->level - 1].linemate; i++)
        server->map.tiles[client->y][client->x].content[1] -= 1;
    for (int i = 0; i < incantation[client->level - 1].deraumere; i++)
        server->map.tiles[client->y][client->x].content[2] -= 1;
    for (int i = 0; i < incantation[client->level - 1].sibur; i++)
        server->map.tiles[client->y][client->x].content[3] -= 1;
    for (int i = 0; i < incantation[client->level - 1].mendiane; i++)
        server->map.tiles[client->y][client->x].content[4] -= 1;
    for (int i = 0; i < incantation[client->level - 1].phiras; i++)
        server->map.tiles[client->y][client->x].content[5] -= 1;
    for (int i = 0; i < incantation[client->level - 1].thystame; i++)
        server->map.tiles[client->y][client->x].content[6] -= 1;
}

bool check_players(server_t *server, client_t *client)
{
    client_t *tmp = NULL;
    tile_t actual_case = server->map.tiles[client->y][client->x];
    bool required = true;
    int total = 0;

    STAILQ_FOREACH(tmp, &server->clients, next) {
        if (tmp->x == actual_case.x && tmp->y == actual_case.y
            && tmp->level == incantation[client->level - 1].level) {
            total += 1;
        }
    }
    if (total != incantation[client->level - 1].nb_player)
        required = false;
    return (required);
}

bool check_stuff(server_t *server, client_t *client)
{
    bool required = true;
    tile_t actual_case = server->map.tiles[client->y][client->x];

    if (actual_case.content[1] != incantation[client->level - 1].linemate)
        required = false;
    if (actual_case.content[2] != incantation[client->level - 1].deraumere)
        required = false;
    if (actual_case.content[3] != incantation[client->level - 1].sibur)
        required = false;
    if (actual_case.content[4] != incantation[client->level - 1].mendiane)
        required = false;
    if (actual_case.content[5] != incantation[client->level - 1].phiras)
        required = false;
    if (actual_case.content[6] != incantation[client->level - 1].thystame)
        required = false;
    return (required);
}

void execute_incantation(server_t *server, client_t *client)
{
    client_t *tmp = NULL;
    char *buff = NULL;
    int old_level = client->level;
    tile_t actual_case = server->map.tiles[client->y][client->x];

    STAILQ_FOREACH(tmp, &server->clients, next) {
        if (tmp->fd < 0 || tmp->graphical || !tmp->team)
            continue;
        if (tmp->x == actual_case.x && tmp->y == actual_case.y
            && tmp->level == incantation[tmp->level - 1].level) {
            dprintf(tmp->fd, "Elevation Underway\n");
            tmp->level += 1;
            tmp->incantation_status = true;
            asprintf(&buff, "%s %d", buff ? buff : "", tmp->id);
        }
    }
    broadcast_graphicals(server, "pic %d %d %d%s\n", client->x,
        client->y, old_level, buff);
    free(buff);
}

int incantation_cmd(server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    client_t *tmp = NULL;
    tile_t actual_case = server->map.tiles[client->y][client->x];

    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    broadcast_graphicals(server, "pie %d %d %s\n", client->x, client->y,
        client->incantation_status ? "ok" : "ko");
    STAILQ_FOREACH(tmp, &server->clients, next) {
        if (tmp->fd < 0 || tmp->graphical || !tmp->team || tmp->x !=
            actual_case.x || tmp->y != actual_case.y || tmp->level !=
            incantation[tmp->level - 1].level)
            continue;
        if (tmp->incantation_status) {
            dprintf(tmp->fd, "Current level: %d\n", tmp->level);
            broadcast_graphicals_func(server, plv_cmd, NULL, tmp);
        } else
            dprintf(tmp->fd, "ko\n");
        tmp->incantation_status = false;
    }
    return (0);
}