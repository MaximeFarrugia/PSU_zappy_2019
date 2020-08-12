/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** player_cmd
*/

#include "server.h"

int connect_nbr_cmd(UNU server_t *server, UNU client_t *client, UNU char **cmd,
    UNU void *c2)
{
    team_t *team = get_team_from_name(&server->teams, client->team);

    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    dprintf(client->fd, "%d\n", team->max_players - team->players);
    return (0);
}

void start_fork(server_t *server, client_t *client)
{
    broadcast_graphicals(server, "pfk %d\n", client->id);
}

int fork_cmd(server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    egg_t *egg = NULL;
    static int idx = 0;

    if (!(egg = new_egg(idx, client->id)))
        return (my_put_error(-1, "Error while creating egg."));
    broadcast_graphicals(server, "enw %d %d %d %d\n", egg->nb ,client->id,
        client->x, client->y);
    STAILQ_INSERT_TAIL(&server->eggs, egg, next);
    dprintf(client->fd, "ok\n");
    idx++;
    return (0);
}

int eject_move_player(server_t *server, client_t *client, client_t *tmp)
{
    int w = server->map.w;
    int h = server->map.h;

    server->map.tiles[tmp->y][tmp->x].players -= 1;
    if (client->orientation == NORTH)
        tmp->y = tmp->y - 1 < 0 ? h - 1 : tmp->y - 1;
    if (client->orientation == SOUTH)
        tmp->y = tmp->y + 1 >= h ? 0 : tmp->y + 1;
    if (client->orientation == EAST)
        tmp->x = tmp->x + 1 >= w ? 0 : tmp->x + 1;
    if (client->orientation == WEST)
        tmp->x = tmp->x - 1 < 0 ? w - 1 : tmp->x - 1;
    server->map.tiles[tmp->y][tmp->x].players += 1;
    dprintf(tmp->fd, "eject: %d\n", !((client->orientation + 2) % 4) ? WEST :
        ((client->orientation + 2) % 4));
    broadcast_graphicals_func(server, ppo_cmd, NULL, tmp);
    return (0);
}

int eject_cmd(server_t *server, client_t *client, UNU char **cmd,
    UNU void *c2)
{
    client_t *tmp = NULL;
    bool found = false;

    if (client->graphical)
        return (dprintf(client->fd, "suc\n"));
    broadcast_graphicals(server, "pex %d\n", client->id);
    STAILQ_FOREACH(tmp, &server->clients, next) {
        if (tmp->fd < 0 || tmp->graphical || !tmp->team ||
            (tmp->x != client->x && tmp->y != client->y) ||
            tmp->id == client->id)
            continue;
        found = true;
        eject_move_player(server, client, tmp);
    }
    return (dprintf(client->fd, found ? "ok\n" : "ko\n"));
}
