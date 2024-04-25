#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN_DISTANCE 1.0 / 5

double dda(float ray[2], double side[2]) {
    unsigned short current[2] = {
        floor(g_data.player.position[0]),
        floor(g_data.player.position[1]),
    };

    float delta[2] = {
        fabs(1 / ray[0]),
        fabs(1 / ray[1]),
    };

    side[0] = ray[0] < 0
        ? (g_data.player.position[0] - current[0]) * delta[0]
        : (current[0] + 1 - g_data.player.position[0]) * delta[0];
    side[1] = ray[1] < 0
        ? (g_data.player.position[1] - current[1]) * delta[1]
        : (current[1] + 1 - g_data.player.position[1]) * delta[1];

    while (true) {
        if (side[0] < side[1])
            current[0] += ray[0] < 0 ? -1 : 1;
        else
            current[1] += ray[1] < 0 ? -1 : 1;

        if (g_data.map.data[current[1] * g_data.map.size[0] + current[0]] != 0)
            break;

        if (side[0] < side[1])
            side[0] += delta[0];
        else
            side[1] += delta[1];
    };
    
    return side[0] < side[1] ? side[0] : side[1];
}

mlx_texture_t value_texture(t_value value) {
    if (value.type == XPM)
        return value.xpm->texture;
    if (value.type == RGBA)
        return (mlx_texture_t){.width = 1, .height = 1, .pixels = (unsigned char *)&value.rgba};
    return (mlx_texture_t){0};
}

unsigned int texture_color(mlx_texture_t texture, unsigned short index[2]) {
    if (texture.bytes_per_pixel != 4) return 0;
    if (index[0] >= texture.width || index[1] >= texture.height) return 0;

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

void draw_floor(mlx_image_t *image, float plane[2]) {
    mlx_texture_t texture_floor = value_texture(g_data.texture.floor);
    mlx_texture_t texture_ceiling = value_texture(g_data.texture.ceiling);

    float ray[4] = {
        g_data.player.direction[0] - plane[0],
        g_data.player.direction[1] - plane[1],
        g_data.player.direction[0] + plane[0],
        g_data.player.direction[1] + plane[1],
    };

    float middle = image->height / 2;
    for(unsigned short y = 0; y < middle; y++)
    {
        float distance = middle / (y - middle);

        double current[2] = {
            distance * ray[0] - g_data.player.position[0],
            distance * ray[1] - g_data.player.position[1],
        };

        float step[2] = {
            distance * (ray[2] - ray[0]) / image->width,
            distance * (ray[3] - ray[1]) / image->width,
        };

        draw(image, (int[4]){0, y, image->width, y}, texture_ceiling,
        (double[]){-current[0] * texture_ceiling.width, current[1] * texture_ceiling.height - 1},
        (float[]){-step[0] * texture_ceiling.width, step[1] * texture_ceiling.height});

        unsigned short reverse_y = image->height - y - 1;
        draw(image, (int[4]){0, reverse_y, image->width, reverse_y}, texture_floor,
        (double[]){-current[0] * texture_floor.width, -current[1] * texture_floor.height},
        (float[]){-step[0] * texture_floor.width, -step[1] * texture_floor.height});
    }
}

void draw_wall(mlx_image_t *image, float plane[2], double distance[]) {
    for (unsigned short x = 0; x < image->width; x++) {
        float norm_x = 2 * x / (double)image->width - 1;
        float ray[2] = {
            g_data.player.direction[0] + plane[0] * norm_x,
            g_data.player.direction[1] + plane[1] * norm_x,
        };

        double side[2];
        distance[x] = dda(ray, side);
        if (distance[x] < MIN_DISTANCE) distance[x] = MIN_DISTANCE;

        int height = image->height / distance[x];
        int line[2] = { -height / 2 + image->height / 2, height / 2 + image->height / 2, };

        t_value value = side[0] < side[1]
            ? ray[0] < 0 ? g_data.texture.west : g_data.texture.east
            : ray[1] < 0 ? g_data.texture.north : g_data.texture.south;
        mlx_texture_t texture = value_texture(value);

        double wall_x = side[0] < side[1]
            ? g_data.player.position[1] + side[0] * ray[1]
            : g_data.player.position[0] + side[1] * ray[0];
        wall_x -= floor(wall_x);

        unsigned short texture_x = wall_x * texture.width;
        if((side[0] < side[1] && ray[0] < 0) || (side[0] > side[1] && ray[1] > 0))
            texture_x = texture.width - texture_x - 1;
        
        draw(image, (int[4]){x, line[0], x, line[1] - 1}, texture,
        (double[]){texture_x, 0}, (float[]){0, (float)texture.height / height});
    }
}

void draw_sprite(mlx_t *mlx, double distance_wall[]) {
    mlx_texture_t texture = value_texture(g_data.texture.sprite);

    unsigned short index = 0;
    for (t_sprite *sprite = g_data.sprites; sprite; sprite = sprite->next) {
        if (sprite->image != NULL) mlx_delete_image(mlx, sprite->image);
        sprite->image = mlx_new_image(mlx, g_data.resolution[0], g_data.resolution[1]);
        mlx_image_to_window(mlx, sprite->image, 0, 0);
        mlx_set_instance_depth(sprite->image->instances, ++index);

        float relative[2] = {
            sprite->position[0] - g_data.player.position[0],
            sprite->position[1] - g_data.player.position[1],
        };
        
        float distance_sprite[2] = {
            g_data.player.direction[0] * relative[1] - g_data.player.direction[1] * relative[0],
            g_data.player.direction[0] * relative[0] + g_data.player.direction[1] * relative[1],
        };
        if (distance_sprite[1] < MIN_DISTANCE) continue;

        unsigned short size[2] = {
            sprite->image->width / distance_sprite[1] / g_data.fov / 2,
            sprite->image->height / distance_sprite[1],
        };

        int screen_x = (sprite->image->width / 2) * (1 + distance_sprite[0] / distance_sprite[1] / g_data.fov);
        if (screen_x < -size[0] / 2 || screen_x >= (int)sprite->image->width + size[0] / 2) continue;

        int pixel[4] = {
            -size[0] / 2 + screen_x,
            -size[1] / 2 + sprite->image->height / 2,
            size[0] / 2 + screen_x,
            size[1] / 2 + sprite->image->height / 2,
        };

        for (int x = pixel[0]; x < pixel[2]; x++) {
            if (x < 0 || x >= (int)sprite->image->width) continue;
            if (distance_sprite[1] >= distance_wall[x]) continue;

            draw(sprite->image, (int[4]){x, pixel[1], x, pixel[3] - 1}, texture,
            (double[]){(x - pixel[0]) * texture.width / size[0], 0},
            (float[]){0, (float)texture.height / size[1]});
        }
    }
}

void loop(void* param) {
    mlx_t *mlx = param;

    static mlx_image_t *image = NULL;
    if (image != NULL) mlx_delete_image(mlx, image);
    image = mlx_new_image(mlx, g_data.resolution[0], g_data.resolution[1]);
    mlx_image_to_window(mlx, image, 0, 0);
    mlx_set_instance_depth(image->instances, 0);

    float plane[2] = { -g_data.fov * g_data.player.direction[1], g_data.fov * g_data.player.direction[0] };
    double distance_wall[g_data.resolution[0]];

    draw_floor(image, plane);
    draw_wall(image, plane, distance_wall);
    draw_sprite(mlx, distance_wall);
}
