/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** socket
*/

#include "server.h"

int setup_socket(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    if (fd < 0)
        return (my_put_error(-1, "Error on socket creation."));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &(int){ 1 },
        sizeof(int)) < 0)
        return (my_put_error(-1, "Error on setsockopt."));
    if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
        return (my_put_error(-1, "Error on socket bind."));
    if (listen(fd, 10) < 0)
        return (my_put_error(-1, "Error on socket listen."));
    return (fd);
}

int select_socket(int sfd, fd_set *rfds, server_t *server)
{
    client_t *client;
    int ret = 0;
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 1 / server->freq;
    FD_ZERO(rfds);
    FD_SET(sfd, rfds);
    STAILQ_FOREACH(client, &server->clients, next) {
        if (client->fd != -1)
            FD_SET(client->fd, rfds);
    }
    if ((ret = select(SOMAXCONN, rfds, NULL, NULL, &timeout)) < 0)
        return (my_put_error(-1, "Error during select."));
    return (ret);
}

int accept_connection(int sfd, client_head_t *head)
{
    struct sockaddr addr;
    socklen_t len;
    int cfd = accept(sfd, &addr, &len);
    client_t *client = NULL;

    if (cfd < 0)
        return (my_put_error(-1, "Error while accepting connection."));
    if (!(client = new_client(cfd)))
        return (my_put_error(-1, "Malloc error."));
    STAILQ_INSERT_TAIL(head, client, next);
    dprintf(cfd, "WELCOME\n");
    return (0);
}