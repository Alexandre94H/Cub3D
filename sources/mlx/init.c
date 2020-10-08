/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:28:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/08 18:40:33 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/X.h>
#include "mlx_full.h"
#include "../library.h"

void			check_resolution(void *mlx, t_file *file)
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
	if (!(texture.data = malloc(sizeof(unsigned int))))
		return texture;
	*texture.data = color;
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

void			init_sprites(void *mlx, t_file *file, t_player *player)
{
	t_sprite		*sprite;
	unsigned char	length;
	unsigned short	x;
	unsigned short	y;

	length = 0;
	while (file->sprites[length])
		init_texture(mlx, file->sprites[length++], TEXTURE_SIDE, TEXTURE_SIDE);
	y = 0;
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x])
		{
			if (file->map[y][x] >= '2' && file->map[y][x] <= '2' + length)
			{
				if (!(sprite = malloc(sizeof(malloc))))
					return ;
				sprite->position = (t_position) {x, y};
				sprite->index = file->map[y][x] - '2';
				file->map[y][x] = '0';
				array_add((void ***)&player->sprites, sprite);
			}
			x++;
		}
		y++;
	}
}

void			loop(char *name, t_runtime runtime)
{
	mlx_do_key_autorepeatoff(runtime.mlx.mlx);
	runtime.mlx.window = mlx_new_window(runtime.mlx.mlx, runtime.file.resolution.width, runtime.file.resolution.height, name);
	mlx_hook(runtime.mlx.window, KeyPress, KeyPressMask, press, &runtime);
	mlx_hook(runtime.mlx.window, KeyRelease, KeyReleaseMask, release, &runtime);
	mlx_loop_hook(runtime.mlx.mlx, update_image, &runtime);
	mlx_loop(runtime.mlx.mlx);
}

void			init_mlx(t_file *file, t_mlx *mlx, t_player *player)
{
	*mlx = (t_mlx) {mlx_init(), 0, 0, 0};
	check_resolution(mlx->mlx, file);
	init_texture(mlx->mlx, &file->north, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->south, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->west, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->east, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->floor, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->ceil, TEXTURE_SIDE, TEXTURE_SIDE);
	init_sprites(mlx->mlx, file, player);
}