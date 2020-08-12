/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** handle_buffered_commands
*/

#include "server.h"

int handle_buffered_commands(server_t *server)
{
    client_t *client = NULL;
    command_t *command = NULL;

    STAILQ_FOREACH(client, &server->clients, next) {
        if (client->fd < 0)
            continue;
        if (!(command = STAILQ_FIRST(&client->commands)))
            continue;
        if (handle_command(server, client, command) < 0)
            return (-1);
    }
    return (0);
}