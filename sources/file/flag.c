/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:24:47 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/19 23:40:26 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_texture		texture(char *line)
{
	t_texture		texture;
	unsigned short	length;

	texture = (t_texture) {0, 0, {TEXTURE_SIDE, TEXTURE_SIDE}};
	length = 0;
	while (line[length] && line[++length] != ' ')
		;
	texture.data = ft_strdup(line, length);
	while (line[++length] == ' ')
		;
	if (*line)
	{
		texture.resolution.width = ft_atoi(line + length);
		while (line[length] && line[++length] != ' ')
			;
		while (line[++length] == ' ')
			;
		texture.resolution.height = ft_atoi(line + length);
	}
	return (texture);
}

void			add_sprite(t_file *file, char *line)
{
	t_texture		*sprite;
	unsigned short	length;

	if (!(sprite = malloc(sizeof(t_texture))))
		return ;
	length = 0;
	while (line[length] && line[++length] != ' ')
		;
	sprite->data = ft_strdup(line, length);
	while (line[++length] == ' ')
		;
	if (*line)
	{
		sprite->resolution.width = ft_atoi(line + length);
		while (line[length] && line[++length] != ' ')
			;
		while (line[++length] == ' ')
			;
		sprite->resolution.height = ft_atoi(line + length);
	}
	else
		sprite->resolution = (t_resolution){TEXTURE_SIDE, TEXTURE_SIDE};
	ft_array_add((void ***)&file->sprites, sprite);
}
