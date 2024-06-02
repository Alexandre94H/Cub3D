#pragma once

#include "MLX42/MLX42.h"

#define MOVEMENT 3.0
#define ROTATION MOVEMENT / 2

#define MIN_DISTANCE 1.0 / 5

#define WIDTH 960
#define HEIGHT 540

typedef struct s_texture {
    mlx_image_t *ceiling;
    mlx_image_t *floor;

    mlx_image_t *north;
    mlx_image_t *south;
    mlx_image_t *west;
    mlx_image_t *east;

    mlx_image_t *sprite;
} t_texture;

typedef struct s_sprite {
    float position[2];
    mlx_image_t *image;

    struct s_sprite *next;
} t_sprite;

typedef struct s_player {
    float position[2];
    float direction[2];
} t_player;

typedef struct s_map {
    char *data;
    unsigned short size[2];
} t_map;

typedef struct s_data {
    mlx_t *mlx;
    float fov;

    t_player player;
    t_map map;

    t_texture texture;
    t_sprite *sprites;
} t_data;

extern t_data g_data;
