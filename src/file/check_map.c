/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:52:45 by ahallain          #+#    #+#             */
/*   Updated: 2020/09/21 15:42:26 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "file_full.h"

int		validate(unsigned char **map, unsigned int *x, unsigned int *y, unsigned char axe)
{
	char	direction;

	if (axe % 2)
	{
		direction = (axe % 4 - 2) * -1;
		if ((int)*x + direction >= 0
			&& *x + direction < ft_strlen((char *)map[*y], 0)
			&& map[*y][*x + direction] != '3')
		{
			*x += direction;
			return (1);
		}
	}
	else
	{
		direction = axe % 4 - 1;
		if ((int)*y + direction >= 0 && map[*y + direction]
			&& *x < ft_strlen((char *)map[*y + direction], 0)
			&& map[*y + direction][*x] != '3')
		{
			*y += direction;
			return (1);
		}
	}
	return (0);
}

int		ship_move(unsigned char **map, unsigned int *x, unsigned int *y, unsigned int *axe)
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

bool	verification(unsigned char **map)
{
	unsigned int	begin;
	unsigned int	x;
	unsigned int	y;
	unsigned int	axe;

	begin = 0;
	while (map[0][begin] == '3')
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