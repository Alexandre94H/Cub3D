/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:18:08 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/08 18:27:52 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

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

int		*ft_data(t_mlx mlx)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	bits_per_pixel = 24;
	size_line = mlx.settings.width * 4;
	endian = 0;
	return ((int *)mlx_get_data_addr(mlx.img,
		&bits_per_pixel, &size_line, &endian));
}

t_mlx		ft_init_mlx(char *title, t_settings settings, t_player player)
{
	t_mlx	mlx;

	ft_putstr("MLX initialization.\n");
	mlx = (t_mlx){settings, player, {0, {0, 0}, 0}, {0, 0, 0, 0, 0 ,0}, 0, 0, 0, 0};
	if (!(mlx.mlx = mlx_init()))
		return (mlx);
	if (!(mlx.win = mlx_new_window(mlx.mlx, settings.width, settings.height,
		title)))
		return (mlx);
	mlx.img = mlx_new_image(mlx.mlx, settings.width, settings.height);
	if (mlx.img)
		mlx.data = ft_data(mlx);
	return (mlx);
}

int			ft_run(char *title, t_settings settings)
{
	t_player	player;
	t_mlx		mlx;

	player = ft_init_player(settings.map);
	if (!player.initiate)
	{
		ft_putstr("Unable to initialize the player.");
		return (4);
	}
	mlx = ft_init_mlx(title, settings, player);
	if (!mlx.img)
	{
		ft_putstr("Unable to initialize the mlx.");
		return (4);
	}
	ft_detect(&mlx);
	return (0);
}
