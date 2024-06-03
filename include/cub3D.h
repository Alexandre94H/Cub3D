#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 320
# define HEIGHT 200
# define MOVEMENT 3.0

# include "MLX42/MLX42.h"
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

//= Types =//

typedef struct player {
    float position[2];
    float direction[2];
} player_t;

typedef struct map {
    char *data;
    unsigned short size[2];
} map_t;

typedef struct sprite {
    struct sprite *next;
    float position[2];
    mlx_image_t *image;
} sprite_t;

typedef enum texture {
    NORTH = 0,
    WEST,
    SOUTH,
    EAST,
    FLOOR,
    CEIL,
    SPRITE,
    TEXTURE_MAX,
} texture_t;

typedef struct data {
    mlx_t *mlx;
    mlx_image_t *texture[TEXTURE_MAX];
    sprite_t *sprites;
    map_t map;
    player_t player;
} data_t;

extern data_t data;

//= Generic Functions =//

void error(int code, char *str, ...);

void parse(char *file);

void loop(void *param);

//= Hook Functions =//

void hook_generic(void *param);

void hook_key(mlx_key_data_t keydata, void *param);

#endif
