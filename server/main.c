/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** main
*/

#include "server.h"

int my_put_error(int code, char *msg)
{
    dprintf(2, "%s\n", msg);
    return (code);
}

int check_errors(server_t *server)
{
    int ret = 0;
    if (STAILQ_FIRST(&server->teams)->max_players < 1)
        ret = my_put_error(-1, "max number of clients must be >= 1.");
    if (server->freq < 2 || server->freq > 10000)
        ret = my_put_error(-1, "-f must be >= 2 and <= 10000.");
    if (server->map.w < 10 || server->map.w > 30)
        ret = my_put_error(-1, "-x must be >= 10 and <= 30.");
    if (server->map.h < 10 || server->map.h > 30)
        ret = my_put_error(-1, "-y must be >= 10 and <= 30.");
    return (ret);
}

int main(int ac, char **av)
{
    int ret = 0;
    int sfd = -1;
    server_t server;

    if (init_server(ac, av, &server) < 0 || check_errors(&server) < 0)
        return (84);
    if ((sfd = setup_socket(server.port)) < 0)
        return (84);
    ret = core(&server, sfd);
    close(sfd);
    return (ret < 0 ? 84 : 0);
}