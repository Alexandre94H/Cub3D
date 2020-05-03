/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:11:06 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/03 09:23:21 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include "../get_next_line/get_next_line.h"

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

	length = 1;
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
		while (--length)
			(*settings).map[length] = copy[length];
	if (copy)
		free(copy);
	return (*settings);
}

char		*ft_hex(char *str)
{
	int		nbr;
	char	*hex;

	nbr = ft_atoi(str);
	hex = 0;
	if (nbr < 16)
		ft_stradhere(&hex, '0');
	else
		ft_stradhere(&hex, "0123456789ABCDEF"[nbr / 16]);
	ft_stradhere(&hex, "0123456789ABCDEF"[nbr % 16]);
	return (hex);
}

char		*ft_line_hex(char *line)
{
	char	*ret;
	char	*current;
	size_t	index;

	ret = ft_hex(line);
	while (*line++ != ',')
		;
	current = ft_hex(line);
	index = 0;
	while (current[index])
		ft_stradhere(&ret, current[index++]);
	free(current);
	while (*line++ != ',')
		;
	current = ft_hex(line);
	index = 0;
	while (current[index])
		ft_stradhere(&ret, current[index++]);
	free(current);
	free(ret);
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
		(*settings).texture.no = line;
	else if (*flag == 'S' && flag[1] == 'O')
		(*settings).texture.so = line;
	else if (*flag == 'W' && flag[1] == 'E')
		(*settings).texture.we = line;
	else if (*flag == 'E' && flag[1] == 'A')
		(*settings).texture.ea = line;
	else if (*flag == 'S')
		(*settings).texture.s = line;
	else if (*flag == 'F')
		(*settings).color.f = ft_line_hex(line);
	else if (*flag == 'C')
		(*settings).color.c = ft_line_hex(line);
	else
		ft_putstr("\033[0m");
	return (*settings);
}
