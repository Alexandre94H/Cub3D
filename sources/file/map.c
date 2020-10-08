/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:31:13 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/08 18:39:47 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "file_full.h"
#include "../library.h"

void	str_add(char **str, char c)
{
	unsigned int	length;
	char			*ret;

	length = 0;
	if (*str)
		length = ft_strlen(*str, '\0');
	length++;
	if (!(ret = malloc(sizeof(char *) * (length + 1))))
		return ;
	ret[length] = 0;
	ret[--length] = c;
	if (*str)
	{
		while (length--)
			ret[length] = (*str)[length];
		free(*str);
	}
	*str = ret;
}

void	map_add(char *line, t_file *file)
{
	unsigned short	length;
	char	**copy;

	length = 0;
	if (file->map)
		while (file->map[length])
			length++;
	length++;
	copy = file->map;
	if (!(file->map = malloc(sizeof(char **) * (length + 1))))
		return ;
	file->map[length] = 0;
	file->map[--length] = 0;
	while (*line)
	{
		str_add((char **)&file->map[length], *line == ' ' ? '.' : *line);
		line++;
	}
	str_add((char **)&file->map[length], '.');
	if (copy)
		while (length--)
			file->map[length] = copy[length];
	if (copy)
		free(copy);
}