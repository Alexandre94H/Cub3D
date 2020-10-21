/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_full.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:31:28 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 19:44:47 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_FULL_H
# define FILE_FULL_H

# include <stdbool.h>
# include "file.h"

# define TEXTURE_SIDE 64

t_resolution	resolution(char *line);
t_texture		texture(char *line);
unsigned char	add_sprite(t_file *file, char *line);
unsigned char	map_add(char *line, t_file *file);
bool			verification(char **map);
unsigned char	scan_file(char *path, t_file *file);
#endif
