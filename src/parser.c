#include "cub3D.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

mlx_image_t *load(char *value) {
    mlx_image_t *image;
    short rgb[3];

    if (sscanf(value, "%hd, %hd, %hd", &rgb[0], &rgb[1], &rgb[2]) == 3) {
        int color = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xff;
        image = mlx_new_image(data.mlx, 1, 1);
        mlx_put_pixel(image, 0, 0, color);
    } else {
        xpm_t *xpm = mlx_load_xpm42(value);
        if (xpm == NULL)
            error(3, "Failed to load xpm %s: %s\n", value, mlx_strerror(mlx_errno));
        image = mlx_texture_to_image(data.mlx, &xpm->texture);
        mlx_delete_xpm42(xpm);
    }

    return image;
}

void header(char *line) {
    char *comp = "NWSEFC";
    textures_t type = strchr(comp, line[0]) - comp;
    if (type == SOUTH && line[1] == ' ') type = SPRITE;
    data.texture[type] = load(strchr(line, ' ') + 1);
}

void map_special(char c, unsigned short position[2]) {
    if (c == ' ') return;

    else if (strchr("NWSE", c) != NULL) {
        int angle = 0;
        if (c == 'N') angle = 0;
        else if (c == 'E') angle = 90;
        else if (c == 'S') angle = 180;
        else if (c == 'W') angle = 270;

        data.player.position[0] = position[0] + 0.5;
        data.player.position[1] = position[1] + 0.5;
        data.player.direction[0] = sin(angle * M_PI / 180);
        data.player.direction[1] = -cos(angle * M_PI / 180);
    }

    else if (c == '2') {
        sprite_t *sprite = malloc(sizeof(sprite_t));
        if (sprite == NULL)
            error(5, "Failed to allocate memory\n");

        sprite->position[0] = position[0] + 0.5;
        sprite->position[1] = position[1] + 0.5;
        sprite->image = NULL;
        sprite->next = NULL;

        if (data.sprites == NULL)
            data.sprites = sprite;
        else {
            sprite_t *last = data.sprites;
            while (last->next != NULL)
                last = last->next;
            last->next = sprite;
        }
    }

    else error(5, "Invalid character %c\n", c);
}

void map(char *line) {
    unsigned short len = strlen(line);
    unsigned short size[2] = {
        data.map.size[0] < len ? len : data.map.size[0],
        data.map.size[1] + 1,
    };

    char *map = malloc(size[0] * size[1]);
    if (map == NULL)
        error(4, "Failed to allocate memory\n");
    bzero(map, size[0] * size[1]);

    for (unsigned short y = 0; y < data.map.size[1]; y++)
        for (unsigned short x = 0; x < data.map.size[0]; x++)
            map[y * size[0] + x] = data.map.data[y * data.map.size[0] + x];

    for (unsigned short x = 0; x < len; x++) {
        char c = line[x];
        if (strchr("01", c) == NULL) {
            map_special(c, (unsigned short[2]){x, size[1] - 1});
            c = '0';
        }
        map[(size[1] - 1) * size[0] + x] = c - '0';
    }

    free(data.map.data);
    data.map.data = map;
    data.map.size[0] = size[0];
    data.map.size[1] = size[1];
}

void parse(char *path) {
    int fd = open(path, O_RDONLY);
    char *line = NULL;
    bool is_header = true;

    if (fd == -1)
        error(2, "Failed to open file %s\n", path);

    while ((line = get_next_line(fd)) != NULL) {
        if (!is_header)
            map(line);
        else if (line[0] == '\0')
            is_header = false;
        else
            header(line);
        free(line);
    }
}
