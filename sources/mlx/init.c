/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:28:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 22:42:31 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/X.h>
#include <stdlib.h>
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

t_sprite		*malloc_sprite(t_sprite sprite)
{
	t_sprite	*copy;

	if (!(copy = malloc(sizeof(t_sprite))))
		return (0);
	copy->position = sprite.position;
	copy->index = sprite.index;
	return (copy);
}

void			init_sprites(void *mlx, t_file *file, t_player *player)
{
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
			if (file->map[y][x] >= '2' && file->map[y][x] < '2' + length)
			{
				array_add((void ***)&player->sprites, malloc_sprite(
					(t_sprite){{x + 0.5, y + 0.5}, file->map[y][x] - '2'}));
				file->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void			loop(char *name, t_runtime runtime)
{
	mlx_do_key_autorepeatoff(runtime.mlx.mlx);
	runtime.mlx.window = mlx_new_window(runtime.mlx.mlx,
		runtime.file.resolution.width, runtime.file.resolution.height, name);
	mlx_hook(runtime.mlx.window, KeyPress, KeyPressMask, press, &runtime);
	mlx_hook(runtime.mlx.window, KeyRelease, KeyReleaseMask, release, &runtime);
	mlx_loop_hook(runtime.mlx.mlx, update, &runtime);
	mlx_loop(runtime.mlx.mlx);
}

void			init_mlx(t_file *file, t_mlx *mlx, t_player *player)
{
	*mlx = (t_mlx) {mlx_init(), 0, 0, 0, 0};
	check_resolution(mlx->mlx, file);
	if (!(mlx->buffer = malloc(sizeof(float *) * file->resolution.width)))
		return ;
	init_texture(mlx->mlx, &file->north, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->south, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->west, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->east, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->floor, TEXTURE_SIDE, TEXTURE_SIDE);
	init_texture(mlx->mlx, &file->ceil, TEXTURE_SIDE, TEXTURE_SIDE);
	init_sprites(mlx->mlx, file, player);
}
