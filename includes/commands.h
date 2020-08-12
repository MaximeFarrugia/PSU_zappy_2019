/*
** EPITECH PROJECT, 2020
** commands
** File description:
** commands
*/

#ifndef COMMANDS_H_
# define COMMANDS_H_

# define UNU __attribute__((unused))

typedef struct server_s server_t;
typedef struct client_s client_t;
typedef struct team_s team_t;
typedef struct tile_s tile_t;
typedef struct command_s command_t;

typedef int (*fptr_t)(server_t *server, client_t *client, char **cmd, void *c2);

typedef struct ftp_command_s ftp_command_t;
struct ftp_command_s
{
    char *cmd;
    fptr_t func;
    int cycle;
};

/* commands/dir_cmd.c */
int forward_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int right_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int left_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/fog_cmd.c */
char *fog_append(tile_t tile, char *buff);
int fog_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/look_cmd.c */
char *realloc_append(char *str, char *append);
tile_t get_tile_anywhere(server_t *server, int x, int y);
tile_t get_tile(server_t *server, client_t *client, int i, int j);
char *append_tile_content(tile_t tile, char *buff);
int look_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/broadcast_cmd.c */
int get_sound_dir(client_t *src, client_t *dst);
char *get_full_message(char **cmd);
int broadcast_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/stuff_cmd.c */
int inventory_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/player_cmd.c */
int connect_nbr_cmd(server_t *server, client_t *client, char **cmd,
    void *c2);
void start_fork(server_t *server, client_t *client);
int fork_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int eject_move_player(server_t *server, client_t *client, client_t *tmp);
int eject_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/object_cmd.c */
int take_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int set_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/incantation_cmd.c */
void delete_items(server_t *server, client_t *client);
bool check_stuff(server_t *server, client_t *client);
bool check_players(server_t *server, client_t *client);
void execute_incantation(server_t *server, client_t *client);
int incantation_cmd(server_t *server, client_t *client, char **cmd,
    void *c2);

/* commands/map_cmd.c */
int msz_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int bct_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int mct_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int tna_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/info_pl_cmd.c */
int ppo_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int plv_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int pin_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int graphic_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int logout_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/time_cmd.c */
int sgt_cmd(server_t *server, client_t *client, char **cmd, void *c2);
int sst_cmd(server_t *server, client_t *client, char **cmd, void *c2);

/* commands/setup_player.c */
void setup_player(server_t *server, client_t *client, team_t *team);
void try_join_as_egg(server_t *server, client_t *client, team_t *team);
void try_join_team(server_t *server, client_t *client, char **cmd);

/* commands/handle_buffered_commands.c */
int handle_buffered_commands(server_t *server);

/* commands/commands.c */
int get_cmd_function_idx(client_t *client, char **input);
int handle_command(server_t *server, client_t *client, command_t *command);
int exec_command(server_t *server, client_t *client, command_t *command);
int read_client(server_t *server, client_t *client);
int read_clients(server_t *server, fd_set *rfds);

#endif /* !COMMANDS_H_ */