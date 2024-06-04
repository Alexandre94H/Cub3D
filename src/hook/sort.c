#include "cub3D.h"
#include <math.h>

static float distance(float position1[2], float position2[2]) {
    return sqrtf(powf(position1[0] - position2[0], 2) + powf(position1[1] - position2[1], 2));
}

void sort_sprite() {
    if (!data.sprites) return;

    sprite_t *last = NULL;
    for (sprite_t *sprite = data.sprites; sprite->next; last = sprite, sprite = sprite->next) {
        sprite_t *next = sprite->next;

        if (distance(data.player.position, sprite->position)
            > distance(data.player.position, next->position))
            continue;

        if (last)
            last->next = next;
        else
            data.sprites = next;

        sprite->next = next->next;
        next->next = sprite;
        sprite = next;
    }
}
