#include "parser.h"
#include "cub3D.h"
#include <stdlib.h>
#include <string.h>

static void increase_size(unsigned short new_size[2]) {
    if (new_size[0] < data.map.size[0]) new_size[0] = data.map.size[0];
    if (new_size[1] < data.map.size[1]) new_size[1] = data.map.size[1];
    if (new_size[0] == data.map.size[0] && new_size[1] == data.map.size[1]) return;

    char *map = malloc(new_size[0] * new_size[1]);
    if (map == NULL) error(4, "Failed to allocate memory\n");

    bzero(map, new_size[0] * new_size[1]);
    for (unsigned short y = 0; y < data.map.size[1]; y++)
        for (unsigned short x = 0; x < data.map.size[0]; x++)
            map[y * new_size[0] + x] = data.map.data[y * data.map.size[0] + x];

    free(data.map.data);
    data.map.data = map;
    data.map.size[0] = new_size[0];
    data.map.size[1] = new_size[1];
}

void map(char *line) {
    unsigned short len = strlen(line);
    increase_size((unsigned short[2]) {len, data.map.size[1] + 1});

    char *map_line = data.map.data + data.map.size[0] * (data.map.size[1] - 1);
    for (unsigned short x = len; x < data.map.size[0]; x++) map_line[x] = 0;

    for (unsigned short x = 0; x < len; x++) {
        char c = line[x];

        if (strchr("01", c) == NULL) {
            populate(c, (unsigned short[2]) {x, data.map.size[1] - 1});
            c = '0';
        }

        map_line[x] = (char) (c - '0');
    }
}
