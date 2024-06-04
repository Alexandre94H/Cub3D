#define MIN_DISTANCE (1.0f / 5.0f)

#include "hook.h"
#include "cub3D.h"
#include <math.h>

static bool can_move(bool horizontal, float update) {
    float position[2] = {data.player.position[0], data.player.position[1]};
    position[!horizontal] += update;

    position[!horizontal] += update < 0 ? -MIN_DISTANCE : MIN_DISTANCE;
    if (data.map.data[(int) position[1] * data.map.size[0] + (int) position[0]] != 0)
        return false;

    position[horizontal] -= update < 0 ? -MIN_DISTANCE : MIN_DISTANCE;
    if (data.map.data[(int) position[1] * data.map.size[0] + (int) position[0]] != 0)
        return false;

    position[horizontal] += (update < 0 ? -MIN_DISTANCE : MIN_DISTANCE) * 2;
    if (data.map.data[(int) position[1] * data.map.size[0] + (int) position[0]] != 0)
        return false;

    return true;
}

void move(const float movement[2]) {
    float update[2] = {
            data.player.direction[0] * movement[0] + data.player.direction[1] * movement[1],

            data.player.direction[1] * movement[0] - data.player.direction[0] * movement[1],
    };

    if (can_move(true, update[0]))
        data.player.position[0] += update[0];
    if (can_move(false, update[1]))
        data.player.position[1] += update[1];

    sort_sprite();
}

void rotate(float rotation) {
    float direction[2] = {data.player.direction[0], data.player.direction[1],};
    data.player.direction[0] = direction[0] * cosf(rotation) - direction[1] * sinf(rotation);
    data.player.direction[1] = direction[0] * sinf(rotation) + direction[1] * cosf(rotation);
}
