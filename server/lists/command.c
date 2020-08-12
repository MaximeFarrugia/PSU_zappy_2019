/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** team
*/

#include "lists.h"

command_t *new_command(char **cmd, int idx)
{
    command_t *command = malloc(sizeof(command_t));

    if (!command)
        return (NULL);
    command->cmd = cmd;
    command->idx = idx;
    command->tricks = true;
    return (command);
}