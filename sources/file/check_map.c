/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:52:45 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 22:20:47 by ahallain         ###   ########.fr       */
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

bool	check_zero_line(char **map, unsigned short x, unsigned short y)
{
	unsigned short	length_x;
	unsigned short	length_y;

	length_y = 0;
	while (map[length_y])
		length_y++;
	if (length_y > y)
	{
		length_x = 0;
		while (map[y][length_x])
			length_x++;
		if (x - 1 >= 0 && length_x > x - 1)
			if (map[y][x - 1] == '0')
				return (false);
		if (length_x > x)
			if (map[y][x] == '0')
				return (false);
		if (length_x > x + 1)
			if (map[y][x + 1] == '0')
				return (false);
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
				if (!(check_zero_line(map, x, y - 1)
					&& check_zero_line(map, x, y)
					&& check_zero_line(map, x, y + 1)))
					return (false);
			x++;
		}
		y++;
	}
	return (ship(map));
}
