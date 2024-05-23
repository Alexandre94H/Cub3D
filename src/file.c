#include "functions.h"
#include "get_next_line.h"
#include "forty_two.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

void load_resolution(char *line) {
    if (sscanf(line, "%hd %hd", &g_data.resolution[0], &g_data.resolution[1]) != 2)
        error(4, "Failed to parse vector\n");
    g_data.fov = (float)g_data.resolution[0] / g_data.resolution[1] / 2;
}

t_value load_value(char *line) {
    short rgb[3] = {0};
    if (sscanf(line, "%hd, %hd, %hd", &rgb[0], &rgb[1], &rgb[2]) == 3)
        return (t_value){
            .type = RGBA,
            .rgba = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF,
        };

    xpm_t *xpm = mlx_load_xpm42(line);
    if (xpm == NULL)
        error(4, "Failed to load xpm %s: %s\n", line, mlx_strerror(mlx_errno));

    return (t_value){
        .type = XPM,
        .xpm = xpm,
    };
}

void load_key(char *line) {
    char *space = ft_strchr(line, ' ');
    if (space == NULL) error(3, "Invalid line %s\n", line);
    *space = '\0';

    char *key = line;
    char *value = space + 1;

    if (ft_strncmp(key, "R", 1) == 0)
        load_resolution(value);
    else if (ft_strncmp(key, "C", 1) == 0)
        g_data.texture.ceiling = load_value(value);
    else if (ft_strncmp(key, "F", 1) == 0)
        g_data.texture.floor = load_value(value);
    else if (ft_strncmp(key, "NO", 2) == 0)
        g_data.texture.north = load_value(value);
    else if (ft_strncmp(key, "SO", 2) == 0)
        g_data.texture.south = load_value(value);
    else if (ft_strncmp(key, "WE", 2) == 0)
        g_data.texture.west = load_value(value);
    else if (ft_strncmp(key, "EA", 2) == 0)
        g_data.texture.east = load_value(value);
    else if (ft_strncmp(key, "S", 1) == 0)
        g_data.texture.sprite = load_value(value);
    else
        error(3, "Unknown key %s\n", line);
}

void load_map(char **lines) {
    t_sprite *last = NULL;
    for (int y = 0; y < g_data.map.size[1]; y++) {
        int x = 0;

        for (char *c = lines[y]; *c; c++) {
            if (*c == ' ')
                *c = '0';

            if (ft_strchr("NESW", *c)) {
                if (g_data.player.position[0] != 0 || g_data.player.position[1] != 0)
                    error(3, "Multiple players\n");

                int angle = 0;
                if (*c == 'N') angle = 0;
                else if (*c == 'E') angle = 90;
                else if (*c == 'S') angle = 180;
                else if (*c == 'W') angle = 270;
                *c = '0';

                g_data.player.position[0] = x + 0.5;
                g_data.player.position[1] = y + 0.5;
                g_data.player.direction[0] = sin(angle * M_PI / 180);
                g_data.player.direction[1] = -cos(angle * M_PI / 180);
            }

            if (*c == '2') {
                *c = '0';

                t_sprite *sprite = malloc(sizeof(t_sprite));
                if (sprite == NULL)
                    error(3, "Failed to allocate memory\n");

                sprite->position[0] = x + 0.5;
                sprite->position[1] = y + 0.5;
                sprite->image = NULL;
                sprite->next = NULL;

                if (last == NULL)
                    g_data.sprites = sprite;
                else
                    last->next = sprite;
                last = sprite;
            }

            if (ft_strchr("01", *c) == NULL)
                error(3, "Invalid character %c\n", *c);
            g_data.map.data[y * g_data.map.size[0] + x++] = *c - '0';
        }

        for (int i = x; i < g_data.map.size[0]; i++)
            g_data.map.data[y * g_data.map.size[0] + i] = 0;

        free(lines[y]);
    }
}

void load_file(char *path) {
    int fd = open(path, O_RDONLY);
    if (fd == -1)
        error(2, "Failed to open file %s\n", path);

    char *map_lines[SHRT_MAX] = {0};

    char *line = NULL;
    while ((line = get_next_line(fd))) {
        if (line[0] == '\0') {
            // Skip empty lines
        } else if (ft_strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", line[0]))
            load_key(line);
        else if (g_data.map.size[1] < SHRT_MAX) {
            map_lines[g_data.map.size[1]++] = line;

            if (ft_strlen(line) > g_data.map.size[0])
                g_data.map.size[0] = ft_strlen(line);
    
            continue;
        }

        free(line);
    }

    g_data.map.data = malloc(g_data.map.size[0] * g_data.map.size[1]);
    if (g_data.map.data == NULL)
        error(2, "Failed to allocate memory\n");
    load_map(map_lines);
}
