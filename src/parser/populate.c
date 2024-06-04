#include "cub3D.h"
#include <stdlib.h>
#include <string.h>

static void player(char c, const float position[2]) {
    if (data.player.position[0] != 0 || data.player.position[1] != 0)
        error(5, "Multiple player positions\n");

    data.player.position[0] = position[0] + 0.5f;
    data.player.position[1] = position[1] + 0.5f;

    if (c == 'N') data.player.direction[1] = -1;
    else if (c == 'E') data.player.direction[0] = 1;
    else if (c == 'S') data.player.direction[1] = 1;
    else if (c == 'W') data.player.direction[0] = -1;
}

static void sprite(const float position[2]) {
    sprite_t *sprite = malloc(sizeof(sprite_t));
    if (sprite == NULL)
        error(5, "Failed to allocate memory\n");

    sprite->next = NULL;
    sprite->image = NULL;
    sprite->position[0] = position[0] + 0.5f;
    sprite->position[1] = position[1] + 0.5f;

    if (data.sprites == NULL)
        data.sprites = sprite;
    else {
        sprite_t *last = data.sprites;
        while (last->next != NULL)
            last = last->next;
        last->next = sprite;
    }
}

void populate(char c, unsigned short position[2]) {
    if (c == ' ') return;
    else if (strchr("NESW", c) != NULL)
        player(c, (float[2]) {position[0], position[1]});
    else if (c == '2')
        sprite((float[2]) {position[0], position[1]});
    else error(5, "Invalid character %c\n", c);
}
