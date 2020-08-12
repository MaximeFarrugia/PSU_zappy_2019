/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** info_pl_cmd
*/

#include "server.h"

int ppo_cmd(server_t *server, client_t *client, char **cmd, void *c2)
{
    int id = 0;
    client_t *tmp = NULL;

    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    if (!c2 && !cmd[1])
        return (dprintf(client->fd, "sbp\n"));
    id = c2 ? ((client_t *)c2)->id : atoi(cmd[1]);
    if (!(tmp = get_client_from_id(&server->clients, id)))
        return (dprintf(client->fd, "sbp\n"));
    dprintf(client->fd, "ppo %d %d %d %d\n", id, tmp->x, tmp->y,
        (int)tmp->orientation);
    return (0);
}

int plv_cmd(server_t *server, client_t *client, char **cmd, void *c2)
{
    int id = 0;
    client_t *tmp = NULL;

    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    if (!c2 && !cmd[1])
        return (dprintf(client->fd, "sbp\n"));
    id = c2 ? ((client_t *)c2)->id : atoi(cmd[1]);
    if (!(tmp = get_client_from_id(&server->clients, id)))
        return (dprintf(client->fd, "sbp\n"));
    dprintf(client->fd, "plv %d %d\n", id, tmp->level);
    return (0);
}

int pin_cmd(server_t *server, client_t *client, char **cmd, void *c2)
{
    int id = 0;
    client_t *tmp = NULL;

    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    if (!c2 && !cmd[1])
        return (dprintf(client->fd, "sbp\n"));
    id = c2 ? ((client_t *)c2)->id : atoi(cmd[1]);
    if (!(tmp = get_client_from_id(&server->clients, id)))
        return (dprintf(client->fd, "sbp\n"));
    dprintf(client->fd, "pin %d %d %d %d %d %d %d %d %d %d\n", id, tmp->x,
        tmp->y,
        tmp->inv[0],
        tmp->inv[1],
        tmp->inv[2],
        tmp->inv[3],
        tmp->inv[4],
        tmp->inv[5],
        tmp->inv[6]);
    return (0);
}

int graphic_cmd(server_t *server, client_t *client, char **cmd,
    UNU void *c2)
{
    if (client->team)
        return (dprintf(client->fd, "ko\n"));
    client->graphical = true;
    msz_cmd(server, client, cmd, NULL);
    sgt_cmd(server, client, cmd, NULL);
    mct_cmd(server, client, cmd, NULL);
    tna_cmd(server, client, cmd, NULL);
    return (0);
}

int logout_cmd(server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    team_t *team = get_team_from_name(&server->teams, client->team);

    if (team) {
        team->players -= 1;
        server->map.tiles[client->y][client->x].players -= 1;
        broadcast_graphicals(server, "pdi %d\n", client->id);
    }
    close(client->fd);
    client->fd = -1;
    free(client->team);
    STAILQ_REMOVE(&server->clients, client, client_s, next);
    free(client);
    return (0);
}