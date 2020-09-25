/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:28:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/09/25 11:13:21 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../lib.h"
#include "mlx_full.h"

void			ft_check_resolution(void *mlx, t_file *file)
{
	unsigned int width;
	unsigned int height;

	mlx_get_screen_size(mlx, (int *)&width, (int *)&height);
	if (file->resolution.width > width)
		file->resolution.width = width;
	if (file->resolution.height > height)
		file->resolution.height = height;
}

t_texture		color(char *line)
{
	unsigned int	color;
	t_texture		texture;

	color = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line < '0' || *line > '9')
		line++;
	color *= 16 * 16;
	color += ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line < '0' || *line > '9')
		line++;
	color *= 16 * 16;
	color += ft_atoi(line);
	texture = (t_texture){0, 0, {1, 1}};
	texture.data = &color;
	return (texture);
}

unsigned int	*image_data(void *image, unsigned short width)
{
	unsigned int	bits_per_pixel;
	unsigned char	endian;

	bits_per_pixel = 32;
	endian = 0;
	width *= 4;
	return ((unsigned int *)mlx_get_data_addr(image, (int *)&bits_per_pixel, (int *)&width, (int *)&endian));
}

void			init_texture(void *mlx, t_texture *texture, unsigned short width, unsigned short height)
{
	char		*path;

	path = (char *)texture->data;
	if (ft_strcchr(path, ','))
	{
		*texture = color(path);
		return ;
	}
	texture->image = mlx_xpm_file_to_image(mlx, path, (int *)&width, (int *)&height);
	texture->data = image_data(texture->image, width);
	texture->resolution.width = width;
	texture->resolution.height = height;
}

void			loop(char *name, t_runtime runtime) {
	runtime.mlx.window = mlx_new_window(runtime.mlx.mlx, runtime.file.resolution.width, runtime.file.resolution.height, name);
	mlx_loop_hook(runtime.mlx.mlx, update_image, &runtime);
	mlx_loop(runtime.mlx.mlx);
}

void			init_mlx(t_file *file, t_mlx *mlx)
{
	*mlx = (t_mlx) {mlx_init(), 0, 0, 0};
	ft_check_resolution(mlx->mlx, file);
	init_texture(mlx->mlx, &file->north, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->south, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->west, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->east, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->sprite, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->floor, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->ceil, TEXTURE_SIDE, TEXTURE_SIDE);
}