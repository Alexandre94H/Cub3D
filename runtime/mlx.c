/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:01:10 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/28 20:42:53 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "runtime.h"
#include "../main/cub3d.h"
#include "../parse/parse.h"
#include "../get_next_line/get_next_line.h"

int			*ft_data(void *img_ptr, int size_line)
{
	int		bits_per_pixel;
	int		endian;

	bits_per_pixel = 32;
	endian = 0;
	size_line *= 4;
	return ((int *)mlx_get_data_addr(img_ptr,
		&bits_per_pixel, &size_line, &endian));
}

void		ft_path_to_data(void *mlx_ptr, t_xpm *xpm, size_t width, size_t height)
{
	int		*data;
	int		x;
	int		y;

	x = width;
	y = height;
	(*xpm).img = mlx_xpm_file_to_image(mlx_ptr, (char *)(*xpm).data, &x, &y);
	data = ft_data((*xpm).img, x);
	free((*xpm).data);
	(*xpm).data = data;
	(*xpm).initiate = 1;
}

void		ft_check_resolution(t_mlx *mlx)
{
	int width;
	int height;

	mlx_get_screen_size((*mlx).mlx, &width, &height);
	if ((int)(*mlx).settings.width > width)
		(*mlx).settings.width = width;
	if ((int)(*mlx).settings.height > height)
		(*mlx).settings.height = height;
}

void		ft_load_texture(void *mlx_ptr, t_xpm *xpm, size_t width, size_t height)
{
	char *path;
	int color;

	path = (char *)(*xpm).data;
	if (ft_strcchr(path, ','))
		color = ft_line_color(path);
	else
	{
		ft_path_to_data(mlx_ptr, xpm, width, height);
		return ;
	}
	if (!((*xpm).data = malloc(sizeof(int *))))
		return ;
	*(*xpm).data = color;
	return ;
}

t_mlx		ft_init_mlx(char *title, t_settings settings, t_player player)
{
	t_mlx	mlx;

	ft_putstr("MLX initialization.\n", 1);
	mlx = (t_mlx){settings, player,
		{0, 0, 0, 0, 0, 0, 0, 0}, mlx_init(), 0, 0, 0};
	if (!settings.bitmap)
	{
		ft_check_resolution(&mlx);
		mlx.win = mlx_new_window(mlx.mlx, mlx.settings.width,
			mlx.settings.height, title);
	}
	ft_load_texture(mlx.mlx, &mlx.settings.textures.no, TEXTURE_SIDE, TEXTURE_SIDE);
	ft_load_texture(mlx.mlx, &mlx.settings.textures.so, TEXTURE_SIDE, TEXTURE_SIDE);
	ft_load_texture(mlx.mlx, &mlx.settings.textures.we, TEXTURE_SIDE, TEXTURE_SIDE);
	ft_load_texture(mlx.mlx, &mlx.settings.textures.ea, TEXTURE_SIDE, TEXTURE_SIDE);
	ft_load_texture(mlx.mlx, &mlx.settings.textures.s, TEXTURE_SIDE, TEXTURE_SIDE);
	ft_load_texture(mlx.mlx, &mlx.settings.textures.c, 1024, 256);
	ft_load_texture(mlx.mlx, &mlx.settings.textures.f, TEXTURE_SIDE, TEXTURE_SIDE);
	return (mlx);
}
