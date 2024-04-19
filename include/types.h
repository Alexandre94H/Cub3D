#pragma once

#include "MLX42/MLX42.h"

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

typedef struct s_vector {
    int x;
    int y;
} t_vector;

typedef struct s_player {
    t_vector pos;
    int angle;
} t_player;

typedef struct s_file {
    t_vector resolution;

    t_value ceiling;
    t_value floor;

    t_value north;
    t_value south;
    t_value west;
    t_value east;

    t_value sprite;

    char *map;
    t_vector map_size;

    t_player player;
} t_file;

typedef struct s_data {
    t_file file;
} t_data;

extern t_data g_data;
