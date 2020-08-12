/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** broadcast_cmd
*/

#include "server.h"

static const int dirs[4][8] = {
    { 1, 8, 7, 6, 5, 4, 3, 2 },
    { 3, 2, 1, 8, 7, 6, 5, 4 },
    { 5, 4, 3, 2, 1, 8, 7, 6 },
    { 7, 6, 5, 4, 3, 2, 1, 8 }
};

int get_sound_dir(client_t *src, client_t *dst)
{
    int dx = src->x < dst->x ? -1 : 1;
    int dy = src->y < dst->y ? 1 : -1;

    if (src->x == dst->x)
        return (dirs[dst->orientation - 1][dy < 0 ? 4 : 0]);
    else if (src->y == dst->y)
        return (dirs[dst->orientation - 1][dx < 0 ? 6 : 2]);
    if (dx < 0 && dy < 0)
        return (dirs[dst->orientation - 1][5]);
    if (dx < 0 && dy > 0)
        return (dirs[dst->orientation - 1][7]);
    if (dx > 0 && dy > 0)
        return (dirs[dst->orientation - 1][1]);
    return (dirs[dst->orientation - 1][3]);
}

char *get_full_message(char **cmd)
{
    char *buff = NULL;

    for (int i = 1; cmd[i]; i++) {
        asprintf(&buff, "%s %s", buff ? buff : "", cmd[i]);
    }
    return (buff);
}

int broadcast_cmd(server_t *server, client_t *client, char **cmd, UNU void *c2)
{
    client_t *tmp = NULL;
    char *buff = NULL;

    if (client->graphical || !cmd[1])
        return (dprintf(client->fd, cmd[1] ? "suc\n" : "ko\n"));
    buff = get_full_message(cmd);
    STAILQ_FOREACH(tmp, &server->clients, next) {
        if (!tmp->fd || !tmp->team || tmp->graphical || tmp->id == client->id)
            continue;
        if (tmp->x == client->x && tmp->y == client->y)
            dprintf(tmp->fd, "message %d,%s\n", 0, buff);
        else {
            dprintf(tmp->fd, "message %d,%s\n",
                get_sound_dir(client, tmp), buff);
        }
    }
    dprintf(client->fd, "ok\n");
    broadcast_graphicals(server, "pbc %d%s\n", client->id, buff);
    free(buff);
    return (0);
}