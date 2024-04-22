#include "types.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double dda(float ray[2], double side[2]) {
    unsigned short current[2] = {
        floor(g_data.player.pos[0]),
        floor(g_data.player.pos[1]),
    };

    float delta[2] = {
        fabs(1 / ray[0]),
        fabs(1 / ray[1]),
    };

    side[0] = ray[0] < 0
        ? (g_data.player.pos[0] - current[0]) * delta[0]
        : (current[0] + 1 - g_data.player.pos[0]) * delta[0];
    side[1] = ray[1] < 0
        ? (g_data.player.pos[1] - current[1]) * delta[1]
        : (current[1] + 1 - g_data.player.pos[1]) * delta[1];

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
    
    return side[0] < side[1] ? side[0] : side[1];
}

unsigned short texture_x(float ray[2], double side[2], unsigned short width) {
    double wall_x = side[0] < side[1]
        ? g_data.player.pos[1] + side[0] * ray[1]
        : g_data.player.pos[0] + side[1] * ray[0];
    wall_x -= floor((wall_x));

    unsigned short x = wall_x * width;
    if((side[0] < side[1] && ray[0] < 0) || (side[0] > side[1] && ray[1] > 0))
        x = g_data.file.north.xpm->texture.width - x - 1;

    return x;
}

void wall_rgb(mlx_image_t *image, unsigned short x, double distance, int rgb) {
    unsigned short height = image->height / distance;
    int start = -height / 2 + image->height / 2;
    int end = height / 2 + (unsigned short)image->height / 2;

    for (int y = start; y < end; y++)
        if (y >= 0 && y < (int)image->height)
            mlx_put_pixel(image, x, y, rgb << 8 | 0xFF);
}

void wall_xpm(mlx_image_t *image, unsigned short x, double distance, xpm_t *xpm, unsigned short xpm_x) {
    unsigned short height = image->height / distance;
    int start = -height / 2 + image->height / 2;
    int end = height / 2 + (unsigned short)image->height / 2;

    float xpm_pos = 0;
    for (int y = start; y < end; y++) {
        int xpm_y = (int)xpm_pos & (xpm->texture.height - 1);
        xpm_pos += (float)xpm->texture.height / height;

        unsigned int color = ((int *)xpm->texture.pixels)[xpm_y * xpm->texture.width + xpm_x];
        if (y >= 0 && y < (int)image->height)
            mlx_put_pixel(image, x, y, color);
    }
}

void wall(mlx_image_t *image) {
    for (unsigned short x = 0; x < image->width; x++) {
        float norm_x = 2 * x / (double)image->width - 1;
        float ray[2] = {
            g_data.player.dir[0] + g_data.player.plane[0] * norm_x,
            g_data.player.dir[1] + g_data.player.plane[1] * norm_x,
        };

        double side[2];
        double distance = dda(ray, side);

        t_value value = side[0] < side[1]
            ? ray[0] < 0 ? g_data.file.west : g_data.file.east
            : ray[1] < 0 ? g_data.file.north : g_data.file.south;

        if (value.type == RGB)
            wall_rgb(image, x, distance, value.rgb);
        else if (value.type == XPM)
            wall_xpm(image, x, distance, value.xpm, texture_x(ray, side, value.xpm->texture.width));
    }
}

void loop(void* param) {
    mlx_t *mlx = param;

    static mlx_image_t *image = NULL;
    if (image != NULL) mlx_delete_image(mlx, image);
    image = mlx_new_image(mlx, g_data.file.resolution[0], g_data.file.resolution[1]);
    mlx_image_to_window(mlx, image, 0, 0);

    wall(image);
}
