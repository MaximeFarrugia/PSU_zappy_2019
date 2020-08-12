/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** fog_cmd
*/

#include "server.h"

char *fog_append(tile_t tile, char *buff)
{
    char *tmp = NULL;

    asprintf(&tmp, " %d %d", tile.x, tile.y);
    buff = realloc_append(buff, tmp);
    free(tmp);
    return (buff);
}

int fog_cmd(UNU server_t *server, UNU client_t *client, UNU char **cmd,
    UNU void *c2)
{
    tile_t tile;
    client_t *tmp = cmd[1] ?
        get_client_from_id(&server->clients, atoi(cmd[1])) : NULL;
    char *buff = tmp ? strdup(cmd[1]) : NULL;

    if (!client->graphical || !cmd[1] || !tmp) {
        free(buff);
        return (dprintf(client->fd, !client->graphical ? "ko\n" : "sbp\n"));
    }
    for (int i = 0; i <= tmp->level; ++i) {
        for (int j = 0; j < 2 * i + 1; ++j) {
            tile = get_tile(server, tmp, i, j - i);
            buff = fog_append(tile, buff);
        }
    }
    dprintf(client->fd, "fog %s\n", buff);
    free(buff);
    return (0);
}