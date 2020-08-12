/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** free
*/

#include "server.h"

int free_commands(command_head_t *head)
{
    command_t *command = NULL;

    while (!STAILQ_EMPTY(head)) {
        command = STAILQ_FIRST(head);
        STAILQ_REMOVE_HEAD(head, next);
        wt_free_tab(command->cmd);
        free(command);
    }
    return (0);
}

int free_clients(client_head_t *head)
{
    client_t *client = NULL;

    while (!STAILQ_EMPTY(head)) {
        client = STAILQ_FIRST(head);
        STAILQ_REMOVE_HEAD(head, next);
        close(client->fd);
        free(client->team);
        free_commands(&client->commands);
        free(client);
    }
    return (0);
}

int free_teams(team_head_t *head)
{
    team_t *team = NULL;

    while (!STAILQ_EMPTY(head)) {
        team = STAILQ_FIRST(head);
        STAILQ_REMOVE_HEAD(head, next);
        free(team->name);
        free(team);
    }
    return (0);
}

int free_map(server_t *server)
{
    for (int i = 0; i < server->map.h; ++i) {
        free(server->map.tiles[i]);
    }
    free(server->map.tiles);
    return (0);
}

int free_server(server_t *server)
{
    free_clients(&server->clients);
    free_teams(&server->teams);
    free_map(server);
    return (0);
}