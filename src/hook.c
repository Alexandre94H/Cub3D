#include "types.h"

#include <math.h>

void sort_sprite() {
    if (!g_data.sprites) return;

    t_sprite *last = NULL;
    for (t_sprite *sprite = g_data.sprites; sprite->next; last = sprite, sprite = sprite->next) {
        t_sprite *next = sprite->next;
        float distance = pow(sprite->position[0] - g_data.player.position[0], 2)
            + pow(sprite->position[1] - g_data.player.position[1], 2);
        float distance_next = pow(next->position[0] - g_data.player.position[0], 2)
            + pow(next->position[1] - g_data.player.position[1], 2);

        if (distance > distance_next) continue;

        if (last)
            last->next = next;
        else
            g_data.sprites = next;

        sprite->next = next->next;
        next->next = sprite;
        sprite = next;
    }
}

void move(float movement[2]) {
    float update[2] = {
        g_data.player.direction[0] * movement[0] + g_data.player.direction[1] * movement[1],
        g_data.player.direction[1] * movement[0] - g_data.player.direction[0] * movement[1],
    };

    unsigned short x = floor(g_data.player.position[0] + update[0]);
    if (g_data.map.data[(int)floor(g_data.player.position[1]) * g_data.map.size[0] + x] == 0)
        g_data.player.position[0] += update[0];

    unsigned short y = floor(g_data.player.position[1] + update[1]);
    if (g_data.map.data[y * g_data.map.size[0] + (int)floor(g_data.player.position[0])] == 0)
        g_data.player.position[1] += update[1];

    sort_sprite();
}

void rotate(float rotation) {
    double direction[2] = { g_data.player.direction[0], g_data.player.direction[1], };
    g_data.player.direction[0] = direction[0] * cos(rotation) - direction[1] * sin(rotation);
    g_data.player.direction[1] = direction[0] * sin(rotation) + direction[1] * cos(rotation);
}

void hook_generic(void* param) {
    mlx_t *mlx = param;
    unsigned short fps = 1 / mlx->delta_time;

    double movement = MOVEMENT / fps;
    double rotation = ROTATION / fps;

    if (mlx_is_key_down(mlx, MLX_KEY_W))
        move((float[2]){ movement, 0 });

    if (mlx_is_key_down(mlx, MLX_KEY_S))
        move((float[2]){ -movement, 0 });

    if (mlx_is_key_down(mlx, MLX_KEY_A))
        move((float[2]){ 0, movement });

    if (mlx_is_key_down(mlx, MLX_KEY_D))
        move((float[2]){ 0, -movement });

    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        rotate(-rotation);

    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        rotate(rotation);
}

void key(mlx_key_data_t keydata, void* param) {
    mlx_t *mlx = param;

    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(mlx);
}

void resize(int32_t width, int32_t height, void* param) {
    (void)param;
    g_data.fov = (float)width / height / 2;
}
