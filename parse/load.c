/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:48:25 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/13 00:47:25 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "parse.h"
#include "../get_next_line/get_next_line.h"
#include "../main/cub3d.h"

char		*ft_stradhere(char **str, char c)
{
	size_t	length;
	char	*ret;

	length = 0;
	if (*str)
		length = ft_strlen(*str, '\0');
	length++;
	if (!(ret = malloc(sizeof(char *) * (length + 1))))
		return ((void *)0);
	ret[length] = 0;
	ret[--length] = c;
	if (*str)
	{
		while (length--)
			ret[length] = (*str)[length];
		free(*str);
	}
	*str = ret;
	return (ret);
}

t_settings	ft_scan(char *line, t_settings *settings)
{
	char	*flag;
	size_t	index;

	if (*line == '\0')
		return (*settings);
	if (*line == ' ' || *line == '1')
		ft_map_line(line, settings);
	else
	{
		index = 0;
		while (line[index++] != ' ')
			;
		if (!(flag = malloc(sizeof(char *) * index)))
			return (*settings);
		flag[--index] = 0;
		while (index--)
			flag[index] = line[index];
		while (*line++ != ' ')
			;
		while (*line == ' ')
			line++;
		ft_flag_set(flag, line, settings);
		free(flag);
	}
	return (*settings);
}

t_settings	ft_load(char *path, t_settings *settings)
{
	int		fd;
	char	*line;
	int		ret;

	ft_putstr("Loading ");
	ft_putstr(path);
	ft_putstr(".\n");
	if ((fd = open(path, O_RDONLY)) == -1)
		return (*settings);
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		ft_scan(line, settings);
		free(line);
	}
	return (*settings);
}
