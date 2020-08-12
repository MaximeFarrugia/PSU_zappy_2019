/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** time_cmd
*/

#include "server.h"

int sgt_cmd(server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    dprintf(client->fd, "sgt %d\n", server->freq);
    return (0);
}

int sst_cmd(server_t *server, client_t *client, char **cmd, UNU void *c2)
{
    int freq = 0;

    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    if (!cmd[1])
        return (dprintf(client->fd, "sbp\n"));
    freq = atoi(cmd[1]);
    server->freq = freq;
    if (freq < 2 || freq > 10000)
        return (dprintf(client->fd, "sbp\n"));
    dprintf(client->fd, "sst %d\n", freq);
    return (0);
}
