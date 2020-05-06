/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/06 23:39:22 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "../get_next_line/get_next_line.h"

int		*ft_data(t_mlx mlx)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	bits_per_pixel = 32;
	size_line = mlx.settings.width * 4;
	endian = 0;
	return ((int *)mlx_get_data_addr(mlx.img,
		&bits_per_pixel, &size_line, &endian));
}

void	ft_update_line(float distance, size_t width, int *data, t_mlx mlx)
{
	int		color;
	size_t	first;
	size_t	height;

	first = (mlx.settings.height - mlx.settings.height / distance) / 2;
	height = 0;
	while (height < mlx.settings.height)
	{
		#include <stdio.h>
		if ((long)first < 0)
			first = 0;
		color = 0;
		if (height < first)
			color = mlx.settings.color.c;
		else if (height > mlx.settings.height - first)
			color = mlx.settings.color.f;
		data[height * mlx.settings.width + width] = color;
		height++;
	}
}

int		ft_update(t_mlx *mlx)
{
	int		*data;
	size_t	width;
	t_ajust	ajust;
	float	distance;

	data = ft_data(*mlx);
	width = 0;
	ajust = ft_ajust((*mlx).player);
	while (width < (*mlx).settings.width)
	{
		distance = ft_distance(2 * width / (float)(*mlx).settings.width - 1, ajust, (*mlx).settings.map);
		ft_update_line(distance, width, data, *mlx);
		width++;
	}
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img, 0, 0);
	return (0);
}
