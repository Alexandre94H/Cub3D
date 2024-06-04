#include "cub3D.h"
#include <stdlib.h>

data_t data = {0};

int main(int argc, char **argv) {
    if (argc != 2)
        error(1, "Usage: %s <file>\n", argv[0]);

    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    mlx_t *mlx = data.mlx = mlx_init(WIDTH, HEIGHT, argv[0], true);

    parse(argv[1]);

    mlx_key_hook(mlx, hook_key, NULL);
    mlx_loop_hook(mlx, hook_generic, NULL);
    mlx_loop_hook(mlx, hook_loop, NULL);

    mlx_loop(mlx);
    mlx_terminate(mlx);

    free(data.map.data);
    while (data.sprites) {
        sprite_t *sav = data.sprites;
        data.sprites = data.sprites->next;
        free(sav);
    }
}
