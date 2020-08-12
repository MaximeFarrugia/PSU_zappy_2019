/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** dir_cmd
*/

#include "server.h"

int forward_cmd(server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    int w = server->map.w;
    int h = server->map.h;

    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    server->map.tiles[client->y][client->x].players -= 1;
    if (client->orientation == NORTH)
        client->y = client->y - 1 < 0 ? h - 1 : client->y - 1;
    if (client->orientation == SOUTH)
        client->y = client->y + 1 >= h ? 0 : client->y + 1;
    if (client->orientation == EAST)
        client->x = client->x + 1 >= w ? 0 : client->x + 1;
    if (client->orientation == WEST)
        client->x = client->x - 1 < 0 ? w - 1 : client->x - 1;
    server->map.tiles[client->y][client->x].players += 1;
    dprintf(client->fd, "ok\n");
    broadcast_graphicals_func(server, ppo_cmd, NULL, client);
    return (0);
}

int right_cmd(UNU server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    if (client->orientation == WEST)
        client->orientation = NORTH;
    else
        client->orientation += 1;
    dprintf(client->fd, "ok\n");
    broadcast_graphicals_func(server, ppo_cmd, NULL, client);
    return (0);
}

int left_cmd(UNU server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    if (client->orientation == NORTH)
        client->orientation = WEST;
    else
        client->orientation -= 1;
    dprintf(client->fd, "ok\n");
    broadcast_graphicals_func(server, ppo_cmd, NULL, client);
    return (0);
}
