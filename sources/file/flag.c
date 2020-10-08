/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:24:47 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/08 18:39:37 by ahallain         ###   ########.fr       */
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
	t_texture	texture;

	texture = (t_texture) {0, 0, {0, 0}};
	texture.data = ft_strdup(line);
	return (texture);
}

void			add_sprite(t_file *file, char *line)
{
	t_texture	*sprite;

	if (!(sprite = malloc(sizeof(t_texture))))
		return ;
	sprite->data = ft_strdup(line);
	array_add((void ***)&file->sprites, sprite);
}
