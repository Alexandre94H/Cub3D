#pragma once

#include "MLX42/MLX42.h"

#define MOVEMENT 3.0
#define ROTATION MOVEMENT / 2

#define MIN_DISTANCE 1.0 / 5

typedef enum e_type {
    RGBA,
    XPM
} t_type;

typedef struct s_value {
    t_type type;
    union {
        unsigned int rgba;
        xpm_t *xpm;
    };
} t_value;

typedef struct s_texture {
    t_value ceiling;
    t_value floor;

    t_value north;
    t_value south;
    t_value west;
    t_value east;

    t_value sprite;
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
    unsigned short resolution[2];
    float fov;

    t_player player;
    t_map map;

    t_texture texture;
    t_sprite *sprites;
} t_data;

extern t_data g_data;
