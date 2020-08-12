/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** commands
*/

#include "server.h"

static const ftp_command_t commands[23] = {
    { "forward", forward_cmd, 7 },
    { "right", right_cmd, 7 },
    { "left", left_cmd, 7 },
    { "look", look_cmd, 7 },
    { "inventory", inventory_cmd, 1 },
    { "broadcast", broadcast_cmd, 7 },
    { "connect_nbr", connect_nbr_cmd, 0 },
    { "fork", fork_cmd, 42 },
    { "eject", eject_cmd, 7 },
    { "take", take_cmd, 7 },
    { "set", set_cmd, 7 },
    { "incantation", incantation_cmd, 300 },
    { "msz", msz_cmd, 0 },
    { "bct", bct_cmd, 0 },
    { "mct", mct_cmd, 0 },
    { "tna", tna_cmd, 0 },
    { "ppo", ppo_cmd, 0 },
    { "plv", plv_cmd, 0 },
    { "pin", pin_cmd, 0 },
    { "sgt", sgt_cmd, 0 },
    { "sst", sst_cmd, 0 },
    { "fog", fog_cmd, 0 },
    { "graphic", graphic_cmd, 0 },
};

int get_cmd_function_idx(client_t *client, char **input)
{
    for (int idx = 0; idx < 23; ++idx) {
        if (!strcasecmp(input[0], commands[idx].cmd)) {
            client->limit = clock();
            return (idx);
        }
    }
    return (-1);
}

int exec_command(server_t *server, client_t *client, command_t *command)
{
    double waiting = (double)(clock() - client->limit) / CLOCKS_PER_SEC;
    int ret = 0;
    int idx = command->idx;

    if ((idx == 7 || idx == 11) && command->tricks) {
        idx == 7 ? start_fork(server, client) :
            start_incantation(server, client);
        command->tricks = false;
    }
    if (waiting >= ((double)commands[idx].cycle / (double)server->freq)) {
        ret = commands[idx].func(server, client, command->cmd, NULL);
        client->limit = clock();
        client_pop_command(client);
        command->tricks = true;
        return (ret);
    }
    return (0);
}

int handle_command(server_t *server, client_t *client, command_t *command)
{
    int ret = 0;

    if (command->idx < 0 && !client->team) {
        try_join_team(server, client, command->cmd);
        client_pop_command(client);
        return (0);
    } else if (command->idx < 0 && client->team) {
        client_pop_command(client);
        dprintf(client->fd, "ko\n");
        return (0);
    }
    ret = exec_command(server, client, command);
    return (ret);
}

int read_client(server_t *server, client_t *client)
{
    char *line = get_next_line(client->fd);
    char **cmd = line ? wordtab(line, (char *[]){ " ", NULL }) : NULL;
    int ret = 0; int idx = 0;

    if (!line)
        ret = logout_cmd(server, client, cmd, NULL);
    else if ((idx = get_cmd_function_idx(client, cmd)) > -2 ||
        (!client->graphical && !client->team))
        ret = add_command_to_client(client, cmd, idx);
    if (line && idx < 0 && client->graphical)
        dprintf(client->fd, "suc\n");
    free(line);
    return (ret);
}

int read_clients(server_t *server, fd_set *rfds)
{
    client_t *client = NULL;
    int ret = 0;

    STAILQ_FOREACH(client, &server->clients, next) {
        if (client->fd != -1 && FD_ISSET(client->fd, rfds)) {
            ret = read_client(server, client);
        }
        if (ret < 0)
            return (-1);
    }
    return (0);
}