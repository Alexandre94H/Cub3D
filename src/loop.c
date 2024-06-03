# define MIN_DISTANCE 1.0 / 5

#include "cub3D.h"
#include <math.h>

double dda(float ray[2], double side[2]) {
    unsigned short current[2] = {
            floor(data.player.position[0]),
            floor(data.player.position[1]),
    };

    float delta[2] = {
            fabs(1 / ray[0]),
            fabs(1 / ray[1]),
    };

    side[0] = ray[0] < 0
              ? (data.player.position[0] - current[0]) * delta[0]
              : (current[0] + 1 - data.player.position[0]) * delta[0];
    side[1] = ray[1] < 0
              ? (data.player.position[1] - current[1]) * delta[1]
              : (current[1] + 1 - data.player.position[1]) * delta[1];

    while (true) {
        if (side[0] < side[1])
            current[0] += ray[0] < 0 ? -1 : 1;
        else
            current[1] += ray[1] < 0 ? -1 : 1;

        if (data.map.data[current[1] * data.map.size[0] + current[0]] != 0)
            break;

        if (side[0] < side[1])
            side[0] += delta[0];
        else
            side[1] += delta[1];
    };

    return side[0] < side[1] ? side[0] : side[1];
}

unsigned int image_color(mlx_image_t *image, unsigned short index[2]) {
    if (index[0] >= image->width || index[1] >= image->height) return 0;

    unsigned char *ptr = image->pixels + (index[1] * image->width + index[0]) * 4;
    return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
}

void draw(mlx_image_t *image[2], int pixel[4], float start[2], float step[2]) {
    double current[2] = {start[0], start[1]};
    for (int x = pixel[0]; x <= pixel[2]; x++)
        for (int y = pixel[1]; y <= pixel[3]; y++) {
            double texture_x = floor(current[0]);
            double texture_y = floor(current[1]);
            texture_x -= floor(texture_x / image[1]->width) * image[1]->width;
            texture_y -= floor(texture_y / image[1]->height) * image[1]->height;
            current[0] += step[0];
            current[1] += step[1];

            if (x >= 0 && x < (int) image[0]->width && y >= 0 && y < (int) image[0]->height)
                mlx_put_pixel(image[0], x, y, image_color(image[1], (unsigned short[]) {texture_x, texture_y}));
        }
}

void draw_floor(mlx_image_t *image, float plane[2]) {
    float ray[4] = {
            data.player.direction[0] - plane[0],
            data.player.direction[1] - plane[1],
            data.player.direction[0] + plane[0],
            data.player.direction[1] + plane[1],
    };

    float middle = image->height / 2;
    for (unsigned short y = 0; y < middle; y++) {
        float distance = middle / (y - middle);

        double current[2] = {
                distance * ray[0] - data.player.position[0],
                distance * ray[1] - data.player.position[1],
        };

        float step[2] = {
                distance * (ray[2] - ray[0]) / image->width,
                distance * (ray[3] - ray[1]) / image->width,
        };

        draw((mlx_image_t *[2]) {image, data.texture[CEIL]}, (int[4]) {0, y, image->width, y},
             (float[]) {-current[0] * data.texture[CEIL]->width, current[1] * data.texture[CEIL]->height},
             (float[]) {-step[0] * data.texture[CEIL]->width, step[1] * data.texture[CEIL]->height});

        unsigned short reverse_y = image->height - y - 1;
        draw((mlx_image_t *[2]) {image, data.texture[FLOOR]}, (int[4]) {0, reverse_y, image->width, reverse_y},
             (float[]) {-current[0] * data.texture[FLOOR]->width, -current[1] * data.texture[FLOOR]->height},
             (float[]) {-step[0] * data.texture[FLOOR]->width, -step[1] * data.texture[FLOOR]->height});
    }
}

void draw_wall(mlx_image_t *image, float plane[2], double distance[]) {
    for (unsigned short x = 0; x < image->width; x++) {
        float norm_x = 2 * x / (float) image->width - 1;
        float ray[2] = {
                data.player.direction[0] + plane[0] * norm_x,
                data.player.direction[1] + plane[1] * norm_x,
        };

        double side[2];
        distance[x] = dda(ray, side);

        int height = image->height / distance[x];
        int line[2] = {-height / 2 + image->height / 2, height / 2 + image->height / 2,};

        mlx_image_t *texture = side[0] < side[1]
                               ? ray[0] < 0 ? data.texture[WEST] : data.texture[EAST]
                               : ray[1] < 0 ? data.texture[NORTH] : data.texture[SOUTH];

        double wall_x = side[0] < side[1]
                        ? data.player.position[1] + side[0] * ray[1]
                        : data.player.position[0] + side[1] * ray[0];
        wall_x -= floor(wall_x);

        unsigned short texture_x = wall_x * texture->width;
        if ((side[0] < side[1] && ray[0] < 0) || (side[0] > side[1] && ray[1] > 0))
            texture_x = texture->width - texture_x - 1;

        draw((mlx_image_t *[2]) {image, texture}, (int[4]) {x, line[0], x, line[1] - 1},
             (float[]) {texture_x, 0}, (float[]) {0, (float) texture->height / height});
    }
}

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

void loop(void *param) {
    static mlx_image_t *image = NULL;
    if (image != NULL) mlx_delete_image(data.mlx, image);
    image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    mlx_image_to_window(data.mlx, image, 0, 0);
    mlx_set_instance_depth(image->instances, 0);

    float fov = (float) data.mlx->width / data.mlx->height / 2;
    float plane[2] = {-fov * data.player.direction[1], fov * data.player.direction[0]};
    double distance_wall[image->width];

    draw_floor(image, plane);
    draw_wall(image, plane, distance_wall);
    draw_sprite(data.mlx, fov, distance_wall);
}
