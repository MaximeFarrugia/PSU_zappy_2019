/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** stuff_cmd
*/

#include "server.h"

int inventory_cmd(UNU server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    dprintf(client->fd, "[ food %d, linemate %d, deraumere %d, sibur %d, "
        "mendiane %d, phiras %d, thystame %d ]\n", client->inv[0],
        client->inv[1], client->inv[2], client->inv[3], client->inv[4],
        client->inv[5], client->inv[6]);
    return (0);
}