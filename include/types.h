#pragma once

#include "MLX42/MLX42.h"

#define MOVEMENT 3.0
#define ROTATION 1.0

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

typedef struct s_map {
    char *data;
    unsigned short size[2];
} t_map;

typedef struct s_player {
    float pos[2];
    double dir[2];
    float plane[2];
} t_player;

typedef struct s_data {
    unsigned short resolution[2];
    t_texture texture;
    t_player player;
    t_map map;
} t_data;

extern t_data g_data;
