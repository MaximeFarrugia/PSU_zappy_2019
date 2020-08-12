/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** object_cmd
*/

#include "server.h"

int take_cmd(server_t *server, client_t *client, char **cmd, UNU void *c2)
{
    int idx = item_to_idx(cmd[1]);

    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    if (!cmd[1])
        return (dprintf(client->fd, "ko\n"));
    if (!server->map.tiles[client->y][client->x].content[idx])
        return (dprintf(client->fd, "ko\n"));
    server->map.tiles[client->y][client->x].content[idx] -= 1;
    client->inv[idx] += 1;
    dprintf(client->fd, "ok\n");
    broadcast_graphicals(server, "pgt %d %d\n", client->id, idx);
    broadcast_graphicals_func(server, pin_cmd, NULL, client);
    broadcast_graphicals_func(server, bct_cmd, NULL,
        &server->map.tiles[client->y][client->x]);
    return (0);
}

int set_cmd(server_t *server, client_t *client, char **cmd, UNU void *c2)
{
    int idx = item_to_idx(cmd[1]);

    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    if (!cmd[1])
        return (dprintf(client->fd, "ko\n"));
    if (!client->inv[idx])
        return (dprintf(client->fd, "ko\n"));
    server->map.tiles[client->y][client->x].content[idx] += 1;
    client->inv[idx] -= 1;
    dprintf(client->fd, "ok\n");
    broadcast_graphicals(server, "pdr %d %d\n", client->id, idx);
    broadcast_graphicals_func(server, pin_cmd, NULL, client);
    broadcast_graphicals_func(server, bct_cmd, NULL,
        &server->map.tiles[client->y][client->x]);
    return (0);
}
