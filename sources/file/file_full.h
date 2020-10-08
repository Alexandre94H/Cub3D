#ifndef		PRIVATE_FULL_H
# define	PRIVATE_FULL_H

#include <stdbool.h>
#include "file.h"

t_resolution	resolution(char *line);
t_texture		texture(char *line);
void			add_sprite(t_file *file, char *line);
void			map_add(char *line, t_file *file);
bool			verification(char **map);
void			scan_file(char *path, t_file *file);
#endif