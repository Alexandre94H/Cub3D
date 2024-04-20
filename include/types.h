#pragma once

#include "MLX42/MLX42.h"

#define FOV 60

typedef enum e_type {
    RGB,
    XPM
} t_type;

typedef struct s_value {
    t_type type;
    union {
        int rgb;
        xpm_t *xpm;
    };
} t_value;

typedef struct s_file {
    unsigned short resolution[2];

    t_value ceiling;
    t_value floor;

    t_value north;
    t_value south;
    t_value west;
    t_value east;

    t_value sprite;

    char *map;
    unsigned short map_size[2];

    unsigned short player_pos[2];
    unsigned short player_angle;
} t_file;

typedef struct s_player {
    float pos[2];
    double dir[2];
    float plane[2];
} t_player;

typedef struct s_data {
    t_file file;
    t_player player;
} t_data;

extern t_data g_data;
