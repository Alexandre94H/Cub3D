/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 00:51:35 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/07 23:17:32 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../get_next_line/get_next_line.h"

int	ft_valdir(char **map, int *x, int *y, int direction)
{
	int	axe;

	if (direction % 2)
	{
		axe = (direction % 4 - 2) * -1;
		if (*x + axe >= 0
			&& *x + axe < (int)ft_strlen(map[*y], 0)
			&& map[*y][*x + axe] != '3')
		{
			*x += axe;
			return (1);
		}
	}
	else
	{
		axe = direction % 4 - 1;
		if (*y + axe >= 0 && map[*y + axe]
			&& *x < (int)ft_strlen(map[*y + axe], 0)
			&& map[*y + axe][*x] != '3')
		{
			*y += axe;
			return (1);
		}
	}
	return (0);
}

int	ft_movship(char **map, int *x, int *y, int *direction)
{
	int way;

	way = 3;
	while (way < 7)
	{
		if (ft_valdir(map, x, y, (*direction + way) % 4))
		{
			*direction = (*direction + way) % 4;
			return (*direction);
		}
		way++;
	}
	return (-1);
}

int	ft_vermap(char **map)
{
	int	begin;
	int	x;
	int	y;
	int	direction;

	begin = 0;
	while (map[0][begin] == '3')
		begin++;
	x = begin;
	y = 0;
	direction = 1;
	while (1)
	{
		if (ft_movship(map, &x, &y, &direction) == -1
			|| map[y][x] != '1')
			return (1);
		if (x == begin && y == 0)
			break ;
	}
	return (0);
}
