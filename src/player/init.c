/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:18:33 by ahallain          #+#    #+#             */
/*   Updated: 2020/09/24 23:37:58 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

unsigned short	degree(char c)
{
	if (c == 'E')
		return (90);
	if (c == 'S')
		return (180);
	if (c == 'W')
		return (270);
	return (0);
}

int		init_player(unsigned char **map, t_player *player)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N'
				|| map[y][x] == 'S'
				|| map[y][x] == 'W'
				|| map[y][x] == 'E')
			{
				*player = (t_player) {degree(map[y][x]), {x, y}};
				return (0);
			}
			x++;
		}
		y++;
	}
	return (3);
}
