#include "rendering.h"
#include "cub3D.h"

void draw_sprite(mlx_t *mlx, float fov, double distance_wall[]) {
    unsigned short index = 0;
    for (sprite_t *sprite = data.sprites; sprite; sprite = sprite->next) {
        if (sprite->image != NULL) mlx_delete_image(mlx, sprite->image);
        sprite->image = mlx_new_image(mlx, WIDTH, HEIGHT);
        mlx_image_to_window(mlx, sprite->image, 0, 0);
        mlx_set_instance_depth(sprite->image->instances, ++index);

        float relative[2] = {
                sprite->position[0] - data.player.position[0],
                sprite->position[1] - data.player.position[1],
        };

        float distance_sprite[2] = {
                data.player.direction[0] * relative[1] - data.player.direction[1] * relative[0],
                data.player.direction[0] * relative[0] + data.player.direction[1] * relative[1],
        };
        if (distance_sprite[1] < MIN_DISTANCE) continue;

        unsigned short size[2] = {
                sprite->image->width / distance_sprite[1] / fov / 2,
                sprite->image->height / distance_sprite[1] * data.texture[SPRITE]->height /
                data.texture[SPRITE]->width,
        };

        int screen_x = (sprite->image->width / 2) * (1 + distance_sprite[0] / distance_sprite[1] / fov);
        if (screen_x < -size[0] / 2 || screen_x >= (int) sprite->image->width + size[0] / 2) continue;

        int pixel[4] = {
                -size[0] / 2 + screen_x,
                -size[1] / 2 + sprite->image->height / 2,
                size[0] / 2 + screen_x,
                size[1] / 2 + sprite->image->height / 2,
        };

        for (int x = pixel[0]; x < pixel[2]; x++) {
            if (x < 0 || x >= (int) sprite->image->width) continue;
            if (distance_sprite[1] >= distance_wall[x]) continue;

            draw((mlx_image_t *[2]) {sprite->image, data.texture[SPRITE]}, (int[4]) {x, pixel[1], x, pixel[3] - 1},
                 (float[]) {(x - pixel[0]) * data.texture[SPRITE]->width / size[0], 0},
                 (float[]) {0, (float) data.texture[SPRITE]->height / size[1]});
        }
    }
}
