#ifndef		PRIVATE_FULL_H
# define	PRIVATE_FULL_H

#define		TEXTURE_SIZE 64

#include <stdbool.h>
#include "file.h"
#include "../../lib/get_next_line/get_next_line.h"

t_resolution	resolution(char *line);
t_texture		texture(char *line);
void			map_add(char *line, t_file *file);
bool			verification(unsigned char **map);
void			scan_file(char *path, t_file *file);
#endif