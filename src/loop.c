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
    wall_x -= floor(wall_x);

    unsigned short x = wall_x * width;
    if((side[0] < side[1] && ray[0] < 0) || (side[0] > side[1] && ray[1] > 0))
        x = width - x - 1;

    return x;
}

void draw_x(mlx_image_t *image, unsigned short y, int line_x[2], mlx_texture_t texture, double current[2], float step[2]) {
    for (int x = line_x[0]; x < line_x[1]; x++) {
        int texture_x = current[0];
        int texture_y = current[1];
        texture_x &= texture.width - 1;
        texture_y &= texture.height - 1;
        current[0] += step[0];
        current[1] += step[1];

        int color = ((int *)texture.pixels)[texture_y * texture.width + texture_x];

        if (x >= 0 && x < (int)image->width)
            mlx_put_pixel(image, x, y, color);
    }
}

void draw_y(mlx_image_t *image, unsigned short x, int line_y[2], mlx_texture_t texture, double current[2], float step[2]) {
    for (int y = line_y[0]; y < line_y[1]; y++) {
        int texture_x = current[0];
        int texture_y = current[1];
        texture_x &= texture.width - 1;
        texture_y &= texture.height - 1;
        current[0] += step[0];
        current[1] += step[1];

        int color = ((int *)texture.pixels)[texture_y * texture.width + texture_x];

        if (y >= 0 && y < (int)image->height)
            mlx_put_pixel(image, x, y, color);
    }
}

void draw_wall(mlx_image_t *image) {
    for (unsigned short x = 0; x < image->width; x++) {
        float norm_x = 2 * x / (double)image->width - 1;
        float ray[2] = {
            g_data.player.dir[0] + g_data.player.plane[0] * norm_x,
            g_data.player.dir[1] + g_data.player.plane[1] * norm_x,
        };

        double side[2];
        unsigned short height = image->height / dda(ray, side);

        int line_y[2] = {
            -height / 2 + image->height / 2,
            height / 2 + image->height / 2,
        };

        t_value value = side[0] < side[1]
            ? ray[0] < 0 ? g_data.file.west : g_data.file.east
            : ray[1] < 0 ? g_data.file.north : g_data.file.south;

        mlx_texture_t texture = value.type == XPM ? value.xpm->texture
            : (mlx_texture_t){.width = 1, .height = 1, .pixels = (unsigned char *)&value.rgba};

        draw_y(image, x, line_y, texture,
        (double[]){texture_x(ray, side, texture.width), 0},
        (float[]){0, (float)texture.height / height});
    }
}

void draw_floor(mlx_image_t *image) {
    float middle = image->height / 2;

    float ray_min[2] = {
        g_data.player.dir[0] - g_data.player.plane[0],
        g_data.player.dir[1] - g_data.player.plane[1],
    };

    float ray_max[2] = {
        g_data.player.dir[0] + g_data.player.plane[0],
        g_data.player.dir[1] + g_data.player.plane[1],
    };

    for(unsigned short y = 0; y < middle; y++)
    {
        float distance = middle / (y - middle);
        xpm_t *xpm = g_data.file.floor.xpm;

        double current[2] = {
            (distance * ray_min[0] - g_data.player.pos[0]) * xpm->texture.width,
            (distance * ray_min[1] - g_data.player.pos[1]) * xpm->texture.height,
        };

        float step[2] = {
            distance * (ray_max[0] - ray_min[0]) / image->width * xpm->texture.width,
            distance * (ray_max[1] - ray_min[1]) / image->width * xpm->texture.height,
        };

        draw_x(image, y, (int[2]){0, image->width}, xpm->texture, current, step);
    }
}

void loop(void* param) {
    mlx_t *mlx = param;

    static mlx_image_t *image = NULL;
    if (image != NULL) mlx_delete_image(mlx, image);
    image = mlx_new_image(mlx, g_data.file.resolution[0], g_data.file.resolution[1]);
    mlx_image_to_window(mlx, image, 0, 0);

    draw_floor(image);
    draw_wall(image);
}
