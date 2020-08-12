/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** init
*/

#include "server.h"

int usage(char *bin)
{
    printf("USAGE: %s -p port -x width -y height -n name1 name2 ... -c "
        "clientsNb -f freq\n"
        "\tport\tis the port number"
        "\twidth\tis the width of the world"
        "\theight\tis the height of the world"
        "\tnameX\tis the name of the team X"
        "\tclientsNb\tis the number of authorized clients per team"
        "\tfreq\tis the reciprocal of time unit for execution of actions", bin);
    return (-1);
}

int init_teams(int ac, char **av, server_t *server, int maxPlayers)
{
    team_t *team = NULL;
    char dflt[4][6] = { "team1", "team2", "team3", "team4" };
    int i = 0;

    while ((optind < ac && av) || (!av && i < 4)) {
        if (optind < ac && av && av[optind][0] == '-')
            break;
        if (!(team = new_team(av ? av[optind] : dflt[i], maxPlayers)))
            return (-1);
        STAILQ_INSERT_TAIL(&server->teams, team, next);
        optind += av ? 1 : 0;
        ++i;
    }
    return (0);
}

int init_map(server_t *server)
{
    if (!(server->map.tiles = malloc(sizeof(tile_t *) * server->map.h)))
        return (-1);
    for (int y = 0; y < server->map.h; ++y) {
        if (!(server->map.tiles[y] = malloc(sizeof(tile_t) * server->map.w)))
            return (-1);
        for (int x = 0; x < server->map.w; ++x)
            fill_tile(server, y, x);
    }
    return (0);
}

int check_params(int ac, char **av, server_t *server, int *maxPlayers)
{
    int opt = -1;

    while ((opt = getopt(ac, av, "p:x:y:c:f:n")) != -1) {
        if (opt == 'p')
            server->port = atoi(optarg);
        if (opt == 'x')
            server->map.w = atoi(optarg);
        if (opt == 'y')
            server->map.h = atoi(optarg);
        if (opt == 'c')
            *maxPlayers = atoi(optarg);
        if (opt == 'f')
            server->freq = atoi(optarg);
        if (opt == 'n' && init_teams(ac, av, server, *maxPlayers) < 0)
            return (-1);
    }
    return (init_map(server));
}

int init_server(int ac, char **av, server_t *server)
{
    int maxPlayers = 3; srand(time(NULL));

    for (int i = 0; i < ac; ++i) {
        if (!strcmp("-help", av[i]))
            return (usage(av[0]));
    }
    STAILQ_INIT(&server->clients);
    STAILQ_INIT(&server->teams);
    STAILQ_INIT(&server->eggs);
    server->port = 4242;
    server->freq = 100;
    server->map.w = 10;
    server->map.h = 10;
    server->winners = NULL;
    check_params(ac, av, server, &maxPlayers);
    if (STAILQ_EMPTY(&server->teams)) {
        if (init_teams(ac, NULL, server, maxPlayers) < 0)
            return (-1);
    }
    return (printf("port: %d\n", server->port));
}