/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** server
*/

#include "server.h"

bool is_running(bool set, bool value)
{
    static bool ret = true;

    if (set)
        ret = value;
    return (ret);
}

void sig_handler(int sig)
{
    (void)sig;
    is_running(true, false);
}

int handle_background_work(server_t *server)
{
    life_manager(server);
    eggs_manager(server);
    spawn_items(server);
    if (handle_buffered_commands(server) < 0)
        return (-1);
    return (0);
}

void endgame(server_t *server)
{
    broadcast_graphicals(server, "seg %s\n", server->winners);
}

int core(server_t *server, int sfd)
{
    int ret = 0;
    fd_set rfds;

    signal(SIGINT, sig_handler);
    while (is_running(false, false) && !server->winners) {
        if (ret < 0 || (ret = select_socket(sfd, &rfds, server)) < 0)
            break;
        else if (!ret) {
            ret = handle_background_work(server);
            continue;
        }
        if (FD_ISSET(sfd, &rfds) &&
            accept_connection(sfd, &server->clients) < 0)
            break;
        else if (!FD_ISSET(sfd, &rfds) && read_clients(server, &rfds) < 0)
            break;
    }
    server->winners ? endgame(server) : 0;
    free_server(server);
    return (0);
}