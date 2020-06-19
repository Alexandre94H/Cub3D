/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:11:06 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/19 05:23:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "../get_next_line/get_next_line.h"
#include "../main/cub3d.h"

char		ft_charline(char *str, size_t length)
{
	if (str[length] == ' ')
		return ('3');
	return (str[length]);
}

t_settings	ft_map_line(char *line, t_settings *settings)
{
	size_t	length;
	char	**copy;

	length = 0;
	if ((*settings).map)
		while ((*settings).map[length])
			length++;
	length++;
	copy = (*settings).map;
	if (!((*settings).map = malloc(sizeof(char **) * (length + 1))))
		return (*settings);
	(*settings).map[length] = 0;
	(*settings).map[--length] = 0;
	while (*line)
	{
		ft_stradhere(&(*settings).map[length], ft_charline(line, 0));
		line++;
	}
	ft_stradhere(&(*settings).map[length], '3');
	if (copy)
		while (length--)
			(*settings).map[length] = copy[length];
	if (copy)
		free(copy);
	return (*settings);
}

int			ft_line_color(char *line)
{
	int	color;

	color = ft_atoi(line);
	while (*line++ != ',')
		;
	color *= 16 * 16;
	color += ft_atoi(line);
	while (*line++ != ',')
		;
	color *= 16 * 16;
	color += ft_atoi(line);
	return (color);
}

void		*ft_strdup(char *str)
{
	char	*ret;
	size_t	index;

	index = ft_strlen(str, 0);
	if (!(ret = malloc(sizeof(char *) * (index + 1))))
		return (0);
	ret[index] = 0;
	while (index--)
		ret[index] = str[index];
	return (ret);
}

t_settings	ft_flag_set(char *flag, char *line, t_settings *settings)
{
	if (*flag == 'R')
	{
		(*settings).width = ft_atoi(line);
		while (*line++ != ' ')
			;
		(*settings).height = ft_atoi(line);
	}
	else if (*flag == 'N' && flag[1] == 'O')
		(*settings).textures.no.data = ft_strdup(line);
	else if (*flag == 'S' && flag[1] == 'O')
		(*settings).textures.so.data = ft_strdup(line);
	else if (*flag == 'W' && flag[1] == 'E')
		(*settings).textures.we.data = ft_strdup(line);
	else if (*flag == 'E' && flag[1] == 'A')
		(*settings).textures.ea.data = ft_strdup(line);
	else if (*flag == 'S')
		(*settings).textures.s.data = ft_strdup(line);
	else if (*flag == 'F')
		(*settings).textures.f.data = ft_strdup(line);
	else if (*flag == 'C')
		(*settings).textures.c.data = ft_strdup(line);
	return (*settings);
}
