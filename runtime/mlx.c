/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:01:10 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/13 00:49:21 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include "runtime.h"
#include "../main/cub3d.h"

int			*ft_data(void *img_ptr, int size_line)
{
	int		bits_per_pixel;
	int		endian;

	bits_per_pixel = 24;
	endian = 0;
	size_line *= 4;
	return ((int *)mlx_get_data_addr(img_ptr,
		&bits_per_pixel, &size_line, &endian));
}

void		ft_path_to_data(void *mlx_ptr, t_xpm *path)
{
	int		*data;
	int		x;
	int		y;

	x = 64;
	y = 64;
	(*path).img = mlx_xpm_file_to_image(mlx_ptr, (char *)(*path).data, &x, &y);
	data = ft_data((*path).img, x);
	free((*path).data);
	(*path).data = data;
}

t_mlx		ft_init_mlx(char *title, t_settings settings, t_player player)
{
	t_mlx	mlx;

	ft_putstr("MLX initialization.\n");
	mlx = (t_mlx){settings, player,
		{0, 0, 0, 0, 0, 0}, 0, 0, 0, 0};
	if (!(mlx.mlx = mlx_init()))
		return (mlx);
	if (!(mlx.win = mlx_new_window(mlx.mlx, settings.width, settings.height,
		title)))
		return (mlx);
	mlx.img = mlx_new_image(mlx.mlx, settings.width, settings.height);
	if (mlx.img)
		mlx.data = ft_data(mlx.img, mlx.settings.width);
	ft_path_to_data(mlx.mlx, &mlx.settings.textures.no);
	ft_path_to_data(mlx.mlx, &mlx.settings.textures.so);
	ft_path_to_data(mlx.mlx, &mlx.settings.textures.we);
	ft_path_to_data(mlx.mlx, &mlx.settings.textures.ea);
	ft_path_to_data(mlx.mlx, &mlx.settings.textures.s);
	mlx_get_screen_size(mlx.mlx, (int *) &settings.width, (int *) &settings.height);
	return (mlx);
}
