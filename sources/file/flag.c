/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:24:47 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 07:44:45 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "file_full.h"
#include "../library.h"

t_resolution	resolution(char *line)
{
	t_resolution resolution;

	resolution = (t_resolution) {0, 0};
	resolution.width = ft_atoi(line);
	while (*++line != ' ')
		;
	while (*++line == ' ')
		;
	resolution.height = ft_atoi(line);
	return (resolution);
}

t_texture		texture_init(char *line, t_texture *texture)
{
	unsigned short	length;

	length = 0;
	if (!ft_strcchr(line, ','))
		while (line[length] && line[++length] != ' ')
			;
	texture->data = (int *)ft_strdup(line, length);
	while (line[length] == ' ')
		length++;
	if (line[length++])
	{
		texture->resolution.width = ft_atoi(line + length);
		while (line[length] && line[++length] != ' ')
			;
		while (line[length] == ' ')
			length++;
		texture->resolution.height = ft_atoi(line + length);
	}
	else
		texture->resolution = (t_resolution){TEXTURE_SIDE, TEXTURE_SIDE};
	return (*texture);
}

t_texture		texture(char *line)
{
	t_texture		texture1;

	texture1 = (t_texture) {0, 0, {0, 0}};
	return (texture_init(line, &texture1));
}

unsigned char	add_sprite(t_file *file, char *line)
{
	t_texture		*sprite;

	if (!(sprite = malloc(sizeof(t_texture))))
		return (0);
	texture_init(line, sprite);
	if (!BONUS && file->sprites)
		return (2);
	ft_array_add((void ***)&file->sprites, sprite);
	return (0);
}
