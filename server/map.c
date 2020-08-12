/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** map
*/

#include "server.h"

void generate_random_item(server_t *server, int y, int x, bool spawn)
{
    int nb_item = (rand() % (100 * ITEM_DENSITY)) / 100;
    int pop = (rand() % ((int)(100 * ITEM_SPAWN))) / 100;
    int nb = rand() % 100;
    int item = 0;

    for (; nb_item != 0 && !spawn; nb_item -= 1) {
        item = (rand() % 6 + 1);
        server->map.tiles[y][x].content[item] += 1;
    }
    if (nb < pop * 100) {
        item = (rand() % 6 + 1);
        server->map.tiles[y][x].content[item] += 1;
    }
}

void generate_random_food(server_t *server, int y, int x, bool spawn)
{
    int food = (rand() % (100 * FOOD_DENSITY)) / 100;
    int pop = (rand() % ((int)(100 * FOOD_SPAWN))) / 100;
    int nb = rand() % 100;

    if (!spawn)
        server->map.tiles[y][x].content[0] = food;
    else if (nb < pop * 500)
        server->map.tiles[y][x].content[0] += 1;
}

void fill_tile(server_t *server, int y, int x)
{
    server->map.tiles[y][x].x = x;
    server->map.tiles[y][x].y = y;
    server->map.tiles[y][x].players = 0;
    generate_random_item(server, y, x, false);
    generate_random_food(server, y, x, false);
}

void spawn_items(server_t *server)
{
    double waiting = (double)(clock() - server->respawn) / CLOCKS_PER_SEC;

    if (waiting < ((double)POPING_CYCLE / (double)server->freq))
        return;
    for (int y = 0; y < server->map.h; ++y) {
        for (int x = 0; x < server->map.w; ++x) {
            generate_random_item(server, y, x, true);
            generate_random_food(server, y, x, true);
        }
    }
    server->respawn = clock();
}