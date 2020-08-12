/*
** EPITECH PROJECT, 2020
** server
** File description:
** server
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <arpa/inet.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include "commands.h"
# include "get_next_line.h"
# include "lists.h"
# include "wordtab.h"

# define ITEM_DENSITY 5
# define FOOD_DENSITY 2
# define UNITS_OF_TIME 126
# define HATCHING_CYCLE 600
# define POPING_CYCLE 35
# define FOOD_SPAWN 0.3
# define ITEM_SPAWN 0.1

typedef struct incantation_s {
    int level;
    int nb_player;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} incantation_t;

typedef struct tile_s {
    int x;
    int y;
    int content[7];
    int players;
} tile_t;

typedef struct map_s {
    int w;
    int h;
    tile_t **tiles;
} map_t;

typedef struct server_s {
    client_head_t clients;
    team_head_t teams;
    egg_head_t eggs;
    map_t map;
    int port;
    int freq;
    clock_t respawn;
    char *winners;
} server_t;

/* broadcast.c */
int broadcast_graphicals(server_t *server, const char *fmt, ...);
int broadcast_graphicals_func(server_t *server,
    int (*func)(server_t *, client_t *, char **, void *), char **cmd, void *c2);

/* core.c */
bool is_running(bool set, bool value);
void sig_handler(int sig);
int handle_background_work(server_t *server);
int core(server_t *server, int sfd);

/* socket.c */
int setup_socket(int port);
int select_socket(int sfd, fd_set *rfds, server_t *server);
int accept_connection(int sfd, client_head_t *head);

/* init.c */
int usage(char *bin);
int init_teams(int ac, char **av, server_t *server, int maxPlayers);
int init_map(server_t *server);
int check_params(int ac, char **av, server_t *server, int *maxPlayers);
int init_server(int ac, char **av, server_t *server);

/* map.c */
void generate_random_item(server_t *server, int y, int x, bool spawn);
void generate_random_food(server_t *server, int y, int x, bool spawn);
void fill_tile(server_t *server, int y, int x);
void spawn_items(server_t *server);

/* life.c */
void eat_to_survive(server_t *server, client_t *client);
void life_manager(server_t *server);

/* eggs.c */
void eggs_manager(server_t *server);
void authorize_new_client(server_t *server, egg_t *egg);
egg_t *new_egg(int nb, int id);

/* check_incantation_cmd.c */
void check_winners(server_t *server, client_t *client);
void start_incantation(server_t *server, client_t *client);

/* items.c */
int item_to_idx(char *item);

/* main.c */
int my_put_error(int code, char *msg);
int check_errors(server_t *server);

#endif /* !SERVER_H_ */