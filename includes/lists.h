/*
** EPITECH PROJECT, 2020
** lists
** File description:
** lists
*/

#ifndef LISTS_H_
# define LISTS_H_

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/queue.h>
# include <unistd.h>
# include <uuid/uuid.h>
# include "wordtab.h"

typedef STAILQ_HEAD(commands, command_s) command_head_t;
typedef STAILQ_HEAD(clients, client_s) client_head_t;
typedef STAILQ_HEAD(teams, team_s) team_head_t;
typedef STAILQ_HEAD(eggs, egg_s) egg_head_t;

typedef struct server_s server_t;

enum orientation {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
};

typedef struct command_s {
    char **cmd;
    int idx;
    bool tricks;
    STAILQ_ENTRY(command_s) next;
} command_t;

typedef struct client_s {
    int fd;
    bool graphical;
    char *team;
    int id;
    int x;
    int y;
    enum orientation orientation;
    int inv[7];
    int level;
    clock_t limit;
    clock_t life;
    command_head_t commands;
    bool incantation_status;
    STAILQ_ENTRY(client_s) next;
} client_t;

typedef struct team_s {
    char *name;
    int max_players;
    int players;
    STAILQ_ENTRY(team_s) next;
} team_t;

typedef struct egg_s {
    int nb;
    int client_id;
    clock_t hatching;
    bool hatched;
    STAILQ_ENTRY(egg_s) next;
} egg_t;

/* free.c */
int free_commands(command_head_t *head);
int free_clients(client_head_t *head);
int free_teams(team_head_t *head);
int free_map(server_t *server);
int free_server(server_t *server);

/* client.c */
client_t *get_client_from_id(client_head_t *head, int id);
client_t *new_client(int cfd);
int add_command_to_client(client_t *client, char **cmd, int idx);
int client_pop_command(client_t *client);

/* team.c */
team_t *get_team_from_name(team_head_t *head, char *name);
team_t *new_team(char *name, int maxPlayers);

/* command.c */
command_t *new_command(char **cmd, int idx);

#endif /* !LISTS_H_ */