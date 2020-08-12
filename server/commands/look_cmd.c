/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** look_cmd
*/

#include "server.h"

char *realloc_append(char *str, char *append)
{
    int len = str ? strlen(str) : 0;

    str = realloc(str, sizeof(char) * (len + strlen(append) + 1));
    str = strcat(str, append);
    return (str);
}

tile_t get_tile_anywhere(server_t *server, int x, int y)
{
    if (x < 0)
        x += server->map.w;
    else
        x = x % server->map.w;
    if (y < 0)
        y += server->map.h;
    else
        y = y % server->map.h;
    return (server->map.tiles[y][x]);
}

tile_t get_tile(server_t *server, client_t *client, int i, int j)
{
    if (client->orientation == NORTH)
        return (get_tile_anywhere(server, client->x + j, client->y - i));
    if (client->orientation == EAST)
        return (get_tile_anywhere(server, client->x + i, client->y + j));
    if (client->orientation == SOUTH)
        return (get_tile_anywhere(server, client->x - j, client->y + i));
    return (get_tile_anywhere(server, client->x - i, client->y - j));
}

char *append_tile_content(tile_t tile, char *buff)
{
    for (int i = 0; i < tile.players; ++i)
        buff = realloc_append(buff, " player");
    for (int i = 0; i < tile.content[0]; ++i)
        buff = realloc_append(buff, " food");
    for (int i = 0; i < tile.content[1]; ++i)
        buff = realloc_append(buff, " linemate");
    for (int i = 0; i < tile.content[2]; ++i)
        buff = realloc_append(buff, " deraumere");
    for (int i = 0; i < tile.content[3]; ++i)
        buff = realloc_append(buff, " sibur");
    for (int i = 0; i < tile.content[4]; ++i)
        buff = realloc_append(buff, " mendiane");
    for (int i = 0; i < tile.content[5]; ++i)
        buff = realloc_append(buff, " phiras");
    for (int i = 0; i < tile.content[6]; ++i)
        buff = realloc_append(buff, " thystame");
    return (buff);
}

int look_cmd(UNU server_t *server, UNU client_t *client, UNU char **cmd,
    UNU void *c2)
{
    tile_t tile;
    char *buff = strdup("[");

    if (client->graphical) {
        free(buff);
        return (dprintf(client->fd, "suc\n"));
    }
    for (int i = 0; i <= client->level; ++i) {
        for (int j = 0; j < 2 * i + 1; ++j) {
            tile = get_tile(server, client, i, j - i);
            buff = append_tile_content(tile, buff);
            buff = realloc_append(buff, i == client->level &&
                j + 1 == 2 * i + 1 ? "]" : ",");
        }
    }
    dprintf(client->fd, "%s\n", buff);
    free(buff);
    return (0);
}