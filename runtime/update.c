/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/04 18:33:02 by ahallain         ###   ########.fr       */
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

void	ft_update(t_mlx mlx)
{
	int		*data;
	size_t	width;
	size_t	height;

	data = ft_data(mlx);
	width = 0;
	while (width < mlx.settings.width)
	{
		height = mlx.settings.height / 2;
		while (height < mlx.settings.height)
		{
			data[(mlx.settings.height - height)
				* mlx.settings.width + width] = mlx.settings.color.c;
			data[height++ * mlx.settings.width + width] = mlx.settings.color.f;
		}
		width++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}
