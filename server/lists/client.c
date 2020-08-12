/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** client
*/

#include "lists.h"

client_t *get_client_from_id(client_head_t *head, int id)
{
    client_t *client = NULL;

    STAILQ_FOREACH(client, head, next) {
        if (client->id == id)
            return (client);
    }
    return (NULL);
}

client_t *new_client(int cfd)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client)
        return (NULL);
    client->fd = cfd;
    client->id = -1;
    client->graphical = false;
    client->team = NULL;
    client->x = -1;
    client->y = -1;
    client->orientation = NORTH;
    for (int i = 1; i < 7; ++i)
        client->inv[i] = 0;
    client->level = 1;
    STAILQ_INIT(&client->commands);
    return (client);
}

int add_command_to_client(client_t *client, char **cmd, int idx)
{
    int count = 0;
    command_t *command = NULL;

    if (!cmd)
        return (0);
    STAILQ_FOREACH(command, &client->commands, next) {
        count += 1;
    }
    if (count >= 10)
        return (wt_free_tab(cmd));
    if (!(command = new_command(cmd, idx)))
        return (wt_free_tab(cmd) | -1);
    STAILQ_INSERT_TAIL(&client->commands, command, next);
    return (0);
}

int client_pop_command(client_t *client)
{
    command_t *command = STAILQ_FIRST(&client->commands);

    if (!command)
        return (0);
    STAILQ_REMOVE_HEAD(&client->commands, next);
    wt_free_tab(command->cmd);
    free(command);
    return (0);
}