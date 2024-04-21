#include "types.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void loop(void* param) {
    mlx_t *mlx = param;

    static mlx_image_t *image = NULL;
    if (image != NULL) mlx_delete_image(mlx, image);
    image = mlx_new_image(mlx, mlx->width, mlx->height);
    mlx_image_to_window(mlx, image, 0, 0);

    for (unsigned short x = 0; x < image->width; x++) {
        float norm_x = 2 * x / (double)image->width - 1;
        float ray[2] = {
            g_data.player.dir[0] + g_data.player.plane[0] * norm_x,
            g_data.player.dir[1] + g_data.player.plane[1] * norm_x,
        };

        unsigned short current[2] = {
            floor(g_data.player.pos[0]),
            floor(g_data.player.pos[1]),
        };

        float delta[2] = {
            fabs(1 / ray[0]),
            fabs(1 / ray[1]),
        };

        double side[2];
        if (ray[0] < 0) side[0] = (g_data.player.pos[0] - current[0]) * delta[0];
        else side[0] = (current[0] + 1 - g_data.player.pos[0]) * delta[0];
        if (ray[1] < 0) side[1] = (g_data.player.pos[1] - current[1]) * delta[1];
        else side[1] = (current[1] + 1 - g_data.player.pos[1]) * delta[1];

        while (true) {
            if (side[0] < side[1])
                current[0] += ray[0] < 0 ? -1 : 1;
            else
                current[1] += ray[1] < 0 ? -1 : 1;

            if (g_data.file.map[current[1] * g_data.file.map_size[0] + current[0]] == 1)
                break;

            if (side[0] < side[1])
                side[0] += delta[0];
            else
                side[1] += delta[1];
        };

        double distance = side[0] < side[1] ? side[0] : side[1];
        unsigned short height = image->height / distance;

        double wall_x = side[0] < side[1]
            ? g_data.player.pos[1] + distance * ray[1]
            : g_data.player.pos[0] + distance * ray[0];
        wall_x -= floor((wall_x));

        unsigned short texture_x = wall_x * g_data.file.north.xpm->texture.width;
        if(side[0] < side[1] && ray[0] > 0) texture_x = g_data.file.north.xpm->texture.width - texture_x - 1;
        if(side[0] > side[1] && ray[1] < 0) texture_x = g_data.file.north.xpm->texture.width - texture_x - 1;

        float step = (float)g_data.file.north.xpm->texture.height / height;
        float texture_pos = 0;

        int start = -height / 2 + image->height / 2;
        int end = height / 2 + image->height / 2;
        
        for (int y = start; y < end; y++) {
            int texture_y = (int)texture_pos & (g_data.file.north.xpm->texture.height - 1);
            texture_pos += step;

            unsigned int color = ((int *)g_data.file.north.xpm->texture.pixels)[texture_y * g_data.file.north.xpm->texture.width + texture_x];

            if (y >= 0 && y < (int)image->height)
                mlx_put_pixel(image, x, y, color);
        }
    }
}
