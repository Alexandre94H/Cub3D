/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:18:08 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/18 20:47:08 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "runtime.h"
#include "../main/cub3d.h"

float		ft_degree(char **map, size_t x, size_t y)
{
	if (map[y][x] == 'N')
		return (0);
	if (map[y][x] == 'E')
		return (90);
	if (map[y][x] == 'S')
		return (180);
	if (map[y][x] == 'W')
		return (270);
	return (-1);
}

t_player	ft_init_player(char **map)
{
	size_t		x;
	size_t		y;
	float		degree;

	ft_putstr("Player initialization.\n");
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((degree = ft_degree(map, x, y)) != -1)
				return ((t_player){degree, {x + .5, y + .5}, 1});
			x++;
		}
		y++;
	}
	return ((t_player){0, {0, 0}, 0});
}

int			ft_run(char *title, t_settings settings)
{
	t_player	player;
	t_mlx		mlx;

	player = ft_init_player(settings.map);
	if (!player.initiate)
		ft_error("Unable to initialize the player.", 3);
	mlx = ft_init_mlx(title, settings, player);
	if (settings.bitmap)
	{
		if (!(mlx.data = malloc(sizeof(int *)
			* (settings.width * settings.height))))
			return (0);
		ft_update(&mlx);
		ft_bitmap(mlx, mlx.settings.bitmap);
		ft_destroy(&mlx);
	}
	else
		ft_detect(&mlx);
	return (0);
}
