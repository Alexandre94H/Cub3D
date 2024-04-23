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
        return width - x - 1;
    return x;
}

mlx_texture_t value_texture(t_value value) {
    if (value.type == XPM)
        return value.xpm->texture;
    if (value.type == RGBA)
        return (mlx_texture_t){.width = 1, .height = 1, .pixels = (unsigned char *)&value.rgba};
    return (mlx_texture_t){0};
}

unsigned int texture_color(mlx_texture_t texture, unsigned short index[2]) {
    if (texture.bytes_per_pixel != 4)
        return 0;

    unsigned char *ptr = texture.pixels + (index[1] * texture.width + index[0]) * 4;
    return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
}

void draw(mlx_image_t *image, int pixel[4], mlx_texture_t texture, double current[2], float step[2]) {
    for (int y = pixel[1]; y <= pixel[3]; y++)
        for (int x = pixel[0]; x <= pixel[2]; x++) {
            int texture_x = current[0];
            int texture_y = current[1];
            texture_x &= texture.width - 1;
            texture_y &= texture.height - 1;
            current[0] += step[0];
            current[1] += step[1];

            if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
                mlx_put_pixel(image, x, y, texture_color(texture, (unsigned short[]){texture_x, texture_y}));
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

    mlx_texture_t texture_floor = value_texture(g_data.file.floor);
    mlx_texture_t texture_ceiling = value_texture(g_data.file.ceiling);

    for(unsigned short y = 0; y < middle; y++)
    {
        float distance = middle / (y - middle);

        double current[2] = {
            distance * ray_min[0] - g_data.player.pos[0],
            distance * ray_min[1] - g_data.player.pos[1],
        };

        float step[2] = {
            distance * (ray_max[0] - ray_min[0]) / image->width,
            distance * (ray_max[1] - ray_min[1]) / image->width,
        };

        draw(image, (int[4]){0, y, image->width, y}, texture_ceiling,
        (double[]){-current[0] * texture_ceiling.width, current[1] * texture_ceiling.height - 1},
        (float[]){-step[0] * texture_ceiling.width, step[1] * texture_ceiling.height});

        unsigned short reverse_y = image->height - y - 1;
        draw(image, (int[4]){0, reverse_y, image->width, reverse_y}, texture_floor,
        (double[]){current[0] * texture_floor.width - 1, current[1] * texture_floor.height - 1},
        (float[]){step[0] * texture_floor.width, step[1] * texture_floor.height});
    }
}

#define MAX_WALL_HEIGHT 5
void draw_wall(mlx_image_t *image, double distance[]) {
    for (unsigned short x = 0; x < image->width; x++) {
        float norm_x = 2 * x / (double)image->width - 1;
        float ray[2] = {
            g_data.player.dir[0] + g_data.player.plane[0] * norm_x,
            g_data.player.dir[1] + g_data.player.plane[1] * norm_x,
        };

        double side[2];
        distance[x] = dda(ray, side);
        if (distance[x] < 1.0 / MAX_WALL_HEIGHT) distance[x] = 1.0 / MAX_WALL_HEIGHT;

        int height = image->height / distance[x];
        int line[2] = { -height / 2 + image->height / 2, height / 2 + image->height / 2, };

        t_value value = side[0] < side[1]
            ? ray[0] < 0 ? g_data.file.west : g_data.file.east
            : ray[1] < 0 ? g_data.file.north : g_data.file.south;
        mlx_texture_t texture = value_texture(value);
        
        draw(image, (int[4]){x, line[0], x, line[1] - 1}, texture,
        (double[]){texture_x(ray, side, texture.width), 0},
        (float[]){0, (float)texture.height / height});
    }
}

void loop(void* param) {
    mlx_t *mlx = param;

    static mlx_image_t *image = NULL;
    if (image != NULL) mlx_delete_image(mlx, image);
    image = mlx_new_image(mlx, g_data.file.resolution[0], g_data.file.resolution[1]);
    mlx_image_to_window(mlx, image, 0, 0);

    double distance[image->width];
    draw_floor(image);
    draw_wall(image, distance);
}
