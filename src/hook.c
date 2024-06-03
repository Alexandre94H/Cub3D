#define MIN_DISTANCE 1.0 / 5

#include "cub3D.h"
#include <math.h>

void sort_sprite() {
    if (data.sprites == NULL) return;

    sprite_t *last = NULL;
    for (sprite_t *sprite = data.sprites; sprite->next; last = sprite, sprite = sprite->next) {
        sprite_t *next = sprite->next;
        float distance = pow(sprite->position[0] - data.player.position[0], 2)
                         + pow(sprite->position[1] - data.player.position[1], 2);
        float distance_next = pow(next->position[0] - data.player.position[0], 2)
                              + pow(next->position[1] - data.player.position[1], 2);

        if (distance > distance_next) continue;

        if (last)
            last->next = next;
        else
            data.sprites = next;

        sprite->next = next->next;
        next->next = sprite;
        sprite = next;
    }
}

bool can_move(bool is_x, float update) {
    float min_distance = MIN_DISTANCE;
    float position[2] = {data.player.position[0], data.player.position[1]};
    position[!is_x] += update;

    position[!is_x] += update < 0 ? -min_distance : min_distance;
    if (data.map.data[(int) position[1] * data.map.size[0] + (int) position[0]] != 0)
        return false;

    position[is_x] -= update < 0 ? -min_distance : min_distance;
    if (data.map.data[(int) position[1] * data.map.size[0] + (int) position[0]] != 0)
        return false;
    position[is_x] += (update < 0 ? -min_distance : min_distance) * 2;
    if (data.map.data[(int) position[1] * data.map.size[0] + (int) position[0]] != 0)
        return false;
    return true;
}

void move(float movement[2]) {
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
    double direction[2] = {data.player.direction[0], data.player.direction[1],};
    data.player.direction[0] = direction[0] * cos(rotation) - direction[1] * sin(rotation);
    data.player.direction[1] = direction[0] * sin(rotation) + direction[1] * cos(rotation);
}

void hook_generic(void *param) {
    unsigned short fps = 1 / data.mlx->delta_time;

    double movement = MOVEMENT / fps;
    double rotation = MOVEMENT / fps / 2;

    if (mlx_is_key_down(data.mlx, MLX_KEY_W))
        move((float[2]) {movement, 0});

    if (mlx_is_key_down(data.mlx, MLX_KEY_S))
        move((float[2]) {-movement, 0});

    if (mlx_is_key_down(data.mlx, MLX_KEY_A))
        move((float[2]) {0, movement});

    if (mlx_is_key_down(data.mlx, MLX_KEY_D))
        move((float[2]) {0, -movement});

    if (mlx_is_key_down(data.mlx, MLX_KEY_LEFT))
        rotate(-rotation);

    if (mlx_is_key_down(data.mlx, MLX_KEY_RIGHT))
        rotate(rotation);
}

void hook_key(mlx_key_data_t keydata, void *param) {
    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(data.mlx);
}
