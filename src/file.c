#include "functions.h"
#include "get_next_line.h"
#include "libft.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void load_resolution(t_file *file, char *line) {
    if (sscanf(line, "%hd %hd", &file->resolution[0], &file->resolution[1]) != 2)
        error(4, "Failed to parse vector\n");
}

t_value load_value(char *line) {
    short rgb[3] = {0};
    if (sscanf(line, "%hd, %hd, %hd", &rgb[0], &rgb[1], &rgb[2]) == 3)
        return (t_value){
            .type = RGB,
            .rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2],
        };

    xpm_t *xpm = mlx_load_xpm42(line);
    if (xpm == NULL)
        error(4, "Failed to load xpm %s: %s\n", line, mlx_strerror(mlx_errno));

    return (t_value){
        .type = XPM,
        .xpm = xpm,
    };
}

void load_key(t_file *file, char *line) {
    char *space = ft_strchr(line, ' ');
    if (!space) error(3, "Invalid line %s\n", line);
    *space = '\0';

    char *key = line;
    char *value = space + 1;

     if (ft_strncmp(key, "R", 1) == 0) {
        load_resolution(file, value);
    } else if (ft_strncmp(key, "C", 1) == 0) {
        file->ceiling = load_value(value);
    } else if (ft_strncmp(key, "F", 1) == 0) {
        file->floor = load_value(value);
    } else if (ft_strncmp(key, "NO", 2) == 0) {
        file->north = load_value(value);
    } else if (ft_strncmp(key, "SO", 2) == 0) {
        file->south = load_value(value);
    } else if (ft_strncmp(key, "WE", 2) == 0) {
        file->west = load_value(value);
    } else if (ft_strncmp(key, "EA", 2) == 0) {
        file->east = load_value(value);
    } else if (ft_strncmp(key, "S", 1) == 0) {
        file->sprite = load_value(value);
    } else
        error(3, "Unknown key %s\n", line);
}

void load_map(t_file *file, char **lines) {
    for (int y = 0; y < file->map_size[1]; y++) {
        int x = 0;

        for (char *c = lines[y]; *c; c++)
            if (*c == ' ')
                file->map[y * file->map_size[0] + x++] = 0;
            else if (ft_strchr("0123456789", *c))
                file->map[y * file->map_size[0] + x++] = *c - '0';
            else {
                file->map[y * file->map_size[0] + x++] = 0;

                if (file->player_pos[0] != 0 || file->player_pos[1] != 0)
                    error(3, "Multiple players\n");

                file->player_pos[0] = x;
                file->player_pos[1] = y;

                if (*c == 'N')
                    file->player_angle = 0;
                else if (*c == 'E')
                    file->player_angle = 90;
                else if (*c == 'S')
                    file->player_angle = 180;
                else if (*c == 'W')
                    file->player_angle = 270;
                else
                    error(3, "Invalid character %c\n", *c);
            }

        for (int i = x; i < file->map_size[0]; i++)
            file->map[y * file->map_size[0] + i] = 0;

        free(lines[y]);
    }
}

t_file load_file(char *filename) {
    t_file file = {0};

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        error(2, "Failed to open file %s\n", filename);

    char *map_lines[SHRT_MAX] = {0};

    char *line = NULL;
    while ((line = get_next_line(fd))) {
        if (line[0] == '\0') {
            // Skip empty lines
        } else if (ft_strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", line[0]))
            load_key(&file, line);
        else if (file.map_size[1] < SHRT_MAX) {
            map_lines[file.map_size[1]++] = line;
            int len = ft_strlen(line);
            if (len > file.map_size[0])
                file.map_size[0] = len;
            continue;
        }

        free(line);
    }

    file.map = malloc(file.map_size[0] * file.map_size[1]);
    if (!file.map)
        error(2, "Failed to allocate memory\n");
    load_map(&file, map_lines);

    return file;
}
