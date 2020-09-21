/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:24:47 by ahallain          #+#    #+#             */
/*   Updated: 2020/09/21 14:45:55 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_full.h"
#include "../lib.h"

t_resolution	resolution(char *line)
{
	t_resolution resolution;

	resolution = (t_resolution) {0, 0};
	resolution.width = ft_atoi(line);
	while (*line++ == ' ')
		;
	resolution.height = ft_atoi(line);
	return (resolution);
}

t_texture	color(char *line)
{
	unsigned int	color;
	t_texture		texture;

	color = ft_atoi(line);
	while (*line < '0' && *line > '9')
		line++;
	color *= 16 * 16;
	color += ft_atoi(line);
	while (*line < '0' && *line > '9')
		line++;
	color *= 16 * 16;
	color += ft_atoi(line);
	texture = (t_texture) {0, {1, 1}};
	*texture.data = color;
	return (texture);
}

t_texture	texture(char *line)
{
	t_texture	texture;
	
	/*if (ft_strcchr(line, ','))
		return (color(line));*/
	texture = (t_texture) {0, {0, 0}};
	texture.data = ft_strdup(line);
	return (texture);
}