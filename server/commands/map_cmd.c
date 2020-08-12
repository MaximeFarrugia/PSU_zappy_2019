/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** map_cmd
*/

#include "server.h"

int msz_cmd(UNU server_t *server, UNU client_t *client, UNU char **cmd,
    UNU void *c2)
{
    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    dprintf(client->fd, "msz %d %d\n", server->map.w, server->map.h);
    return (0);
}

int bct_cmd(server_t *server, client_t *client, char **cmd, void *c2)
{
    int x = 0;
    int y = 0;

    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    if (!c2 && (!cmd[1] || !cmd[2]))
        return (dprintf(client->fd, "sbp\n"));
    x = c2 ? ((tile_t *)c2)->x : atoi(cmd[1]);
    y = c2 ? ((tile_t *)c2)->y : atoi(cmd[2]);
    if (x < 0 || x > server->map.w || y < 0 || y > server->map.h)
        return (dprintf(client->fd, "sbp\n"));
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        server->map.tiles[y][x].content[0],
        server->map.tiles[y][x].content[1],
        server->map.tiles[y][x].content[2],
        server->map.tiles[y][x].content[3],
        server->map.tiles[y][x].content[4],
        server->map.tiles[y][x].content[5],
        server->map.tiles[y][x].content[6]);
    return (0);
}

int mct_cmd(server_t *server, client_t *client, UNU char **cmd, UNU void *c2)
{
    char *sx = NULL;
    char *sy = NULL;

    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    for (int x = 0; x < server->map.w; ++x) {
        asprintf(&sx, "%d", x);
        for (int y = 0; y < server->map.h; ++y) {
            asprintf(&sy, "%d", y);
            bct_cmd(server, client, (char *[]){ "bct", sx, sy, NULL }, NULL);
            free(sy);
        }
        free(sx);
    }
    return (0);
}

int tna_cmd(UNU server_t *server, UNU client_t *client, UNU char **cmd,
    UNU void *c2)
{
    team_t *team = NULL;

    if (!client->graphical)
        return (dprintf(client->fd, "ko\n"));
    STAILQ_FOREACH(team, &server->teams, next) {
        dprintf(client->fd, "tna %s\n", team->name);
    }
    return (0);
}
