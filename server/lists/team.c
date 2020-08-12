/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** team
*/

#include "lists.h"

team_t *get_team_from_name(team_head_t *head, char *name)
{
    team_t *team = NULL;

    if (!name)
        return (NULL);
    STAILQ_FOREACH(team, head, next) {
        if (!strcasecmp(name, team->name))
            return (team);
    }
    return (NULL);
}

team_t *new_team(char *name, int maxPlayers)
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        return (NULL);
    if (!(team->name = strdup(name)))
        return (NULL);
    team->max_players = maxPlayers;
    team->players = 0;
    return (team);
}