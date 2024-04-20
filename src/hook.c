#include "types.h"

#include <math.h>

void key(mlx_key_data_t keydata, void* param) {
    mlx_t *mlx = param;
    (void)mlx;

    if (keydata.action == MLX_RELEASE)
        return;

    double movement = 0.1;
    double rotation = 0.1;

    if (keydata.key == MLX_KEY_W) {
        g_data.player.pos[0] += g_data.player.dir[0] * movement;
        g_data.player.pos[1] += g_data.player.dir[1] * movement;
    }

    if (keydata.key == MLX_KEY_S) {
        g_data.player.pos[0] -= g_data.player.dir[0] * movement;
        g_data.player.pos[1] -= g_data.player.dir[1] * movement;
    }

    if (keydata.key == MLX_KEY_A) {
        double dir[2] = { g_data.player.dir[0], g_data.player.dir[1], };
        g_data.player.dir[0] = dir[0] * cos(-rotation) - dir[1] * sin(-rotation);
        g_data.player.dir[1] = dir[0] * sin(-rotation) + dir[1] * cos(-rotation);

        double plane[2] = { g_data.player.plane[0], g_data.player.plane[1], };
        g_data.player.plane[0] = plane[0] * cos(-rotation) - plane[1] * sin(-rotation);
        g_data.player.plane[1] = plane[0] * sin(-rotation) + plane[1] * cos(-rotation);
    }

    if (keydata.key == MLX_KEY_D) {
        double dir[2] = { g_data.player.dir[0], g_data.player.dir[1], };
        g_data.player.dir[0] = dir[0] * cos(rotation) - dir[1] * sin(rotation);
        g_data.player.dir[1] = dir[0] * sin(rotation) + dir[1] * cos(rotation);

        double plane[2] = { g_data.player.plane[0], g_data.player.plane[1], };
        g_data.player.plane[0] = plane[0] * cos(rotation) - plane[1] * sin(rotation);
        g_data.player.plane[1] = plane[0] * sin(rotation) + plane[1] * cos(rotation);
    }    
}
