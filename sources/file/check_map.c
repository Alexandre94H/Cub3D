/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:52:45 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 15:43:00 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "file_full.h"
#include "../library.h"

int		validate(char **map, unsigned short *x, unsigned short *y,
	unsigned char axe)
{
	char	direction;

	if (axe % 2)
	{
		direction = (axe % 4 - 2) * -1;
		if (*x + direction >= 0
			&& *x + direction < (unsigned short)ft_strlen(map[*y], 0)
			&& map[*y][*x + direction] != ' ')
		{
			*x += direction;
			return (1);
		}
	}
	else
	{
		direction = axe % 4 - 1;
		if (*y + direction >= 0 && map[*y + direction]
			&& *x < ft_strlen(map[*y + direction], 0)
			&& map[*y + direction][*x] != ' ')
		{
			*y += direction;
			return (1);
		}
	}
	return (0);
}

int		ship_move(char **map, unsigned short *x, unsigned short *y,
	unsigned char *axe)
{
	unsigned char way;

	way = 3;
	while (way < 7)
	{
		if (validate(map, x, y, (*axe + way) % 4))
		{
			*axe = (*axe + way) % 4;
			return (*axe);
		}
		way++;
	}
	return (-1);
}

bool	ship(char **map)
{
	unsigned short	begin;
	unsigned short	x;
	unsigned short	y;
	unsigned char	axe;

	begin = 0;
	while (map[0][begin] == ' ')
		begin++;
	x = begin;
	y = 0;
	axe = 1;
	while (1)
	{
		if (ship_move(map, &x, &y, &axe) == -1
			|| map[y][x] != '1')
			return (false);
		if (x == begin && y == 0)
			break ;
	}
	return (true);
}

bool	verification(char **map)
{
	unsigned short	x;
	unsigned short	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
			{
				if (map[y][x - 1] == '0' || map[y][x + 1] == '0')
					return (false);
				if (y - 1 >= 0 && (map[y - 1][x - 1] == '0'
					|| map[y - 1][x] == '0' || map[y - 1][x + 1] == '0'))
					return (false);
				if (map[y + 1] && (map[y + 1][x - 1] == '0'
					|| map[y + 1][x] == '0' || map[y + 1][x + 1] == '0'))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (ship(map));
}

bool	is_init(t_file file)
{
	if (!file.resolution.height
		|| !file.north.data
		|| !file.south.data
		|| !file.east.data
		|| !file.west.data
		|| !file.floor.data
		|| !file.ceil.data
		|| !file.sprites)
		return (false);
	return (true);
}
