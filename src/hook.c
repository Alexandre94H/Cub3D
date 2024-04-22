#include "types.h"

#include <math.h>
#include <sys/time.h>

void move(float movement) {
    float update[2] = { movement * g_data.player.dir[0], movement * g_data.player.dir[1] };

    unsigned short x = floor(g_data.player.pos[0] + update[0]);
    if (g_data.file.map[(int)floor(g_data.player.pos[1]) * g_data.file.map_size[0] + x] != 1)
        g_data.player.pos[0] += update[0];

    unsigned short y = floor(g_data.player.pos[1] + update[1]);
    if (g_data.file.map[y * g_data.file.map_size[0] + (int)floor(g_data.player.pos[0])] != 1)
        g_data.player.pos[1] += update[1];
}

void rotate(float rotation) {
    double dir[2] = { g_data.player.dir[0], g_data.player.dir[1], };
    g_data.player.dir[0] = dir[0] * cos(rotation) - dir[1] * sin(rotation);
    g_data.player.dir[1] = dir[0] * sin(rotation) + dir[1] * cos(rotation);

    double plane[2] = { g_data.player.plane[0], g_data.player.plane[1], };
    g_data.player.plane[0] = plane[0] * cos(rotation) - plane[1] * sin(rotation);
    g_data.player.plane[1] = plane[0] * sin(rotation) + plane[1] * cos(rotation);
}

void hook_generic(void* param) {
    mlx_t *mlx = param;
    unsigned short fps = 1 / mlx->delta_time;

    double movement = MOVEMENT / fps;
    double rotation = ROTATION / fps;

    if (mlx_is_key_down(mlx, MLX_KEY_W))
        move(movement);

    if (mlx_is_key_down(mlx, MLX_KEY_S))
        move(-movement);

    if (mlx_is_key_down(mlx, MLX_KEY_A))
        rotate(-rotation);

    if (mlx_is_key_down(mlx, MLX_KEY_D))
        rotate(rotation); 
}

void key(mlx_key_data_t keydata, void* param) {
    mlx_t *mlx = param;

    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(mlx);
}
