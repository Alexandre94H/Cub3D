#include "functions.h"
#include "get_next_line.h"
#include "libft.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

t_vector load_vector(char *line) {
    t_vector vector = {0};
    if (sscanf(line, "%d %d", &vector.x, &vector.y) != 2)
        error(4, "Failed to parse vector\n");
    return vector;
}

t_value load_value(char *line) {
    short rgb[3] = {0};
    if (sscanf(line, "%hd, %hd, %hd", &rgb[0], &rgb[1], &rgb[2]) == 3)
        return (t_value){
            .type = RGB,
            .rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2],
        };

    return (t_value){
        .type = XPM,
        .xpm = mlx_load_xpm42(line),
    };
}

void load_key(t_file *file, char *line) {
    char *space = ft_strchr(line, ' ');
    if (!space) error(3, "Invalid line %s\n", line);
    *space = '\0';

    char *key = line;
    char *value = space + 1;

     if (ft_strncmp(key, "R", 1) == 0) {
        file->resolution = load_vector(value);
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
    for (int y = 0; y < file->map_size.y; y++) {
        int x = 0;
        for (char *c = lines[y]; *c; c++)
            if (*c == ' ')
                file->map[y * file->map_size.x + x++] = 0;
            else if (ft_strchr("0123456789", *c))
                file->map[y * file->map_size.x + x++] = *c - '0';
            else {
                file->map[y * file->map_size.x + x++] = 0;

                int angle = 0;
                if (*c == 'N')
                    angle = 0;
                else if (*c == 'E')
                    angle = 90;
                else if (*c == 'S')
                    angle = 180;
                else if (*c == 'W')
                    angle = 270;
                else
                    error(3, "Invalid character %c\n", *c);

                file->player = (t_player){
                    .pos = {x, y},
                    .angle = angle,
                };
            }
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
        else if (file.map_size.y < SHRT_MAX) {
            map_lines[file.map_size.y++] = line;
            int len = ft_strlen(line);
            if (len > file.map_size.x)
                file.map_size.x = len;
            continue;
        }

        free(line);
    }

    file.map = malloc(file.map_size.x * file.map_size.y);
    if (!file.map)
        error(2, "Failed to allocate memory\n");
    load_map(&file, map_lines);

    return file;
}