/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:28:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/20 19:15:00 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mlx_full.h"
#include "../library.h"

void			check_resolution(void *mlx, t_resolution *resolution)
{
	unsigned int width;
	unsigned int height;

	mlx_get_screen_size(mlx, (int *)&width, (int *)&height);
	if (resolution->width > width)
		resolution->width = width;
	if (resolution->height > height)
		resolution->height = height;
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

unsigned short	init_sprites(void *mlx, t_file *file, t_player *player)
{
	unsigned char	length;
	unsigned short	x;
	unsigned short	y;

	x = 0;
	length = 0;
	while (!x && file->sprites[length])
		x = init_texture(mlx, file->sprites[length++]);
	y = -1;
	if (!x)
		while (file->map[++y])
		{
			while (file->map[y][x])
			{
				if (file->map[y][x] >= '2' && file->map[y][x] < '2' + length)
				{
					ft_array_add((void ***)&player->sprites, malloc_sprite(
						(t_sprite){{x + 0.5, y + 0.5}, file->map[y][x] - '2'}));
					file->map[y][x] = '0';
				}
				x++;
			}
			x = 0;
		}
	return (x);
}

unsigned char	init_mlx(t_file *file, t_mlx *mlx, t_player *player)
{
	unsigned char	ret;

	*mlx = (t_mlx) {mlx_init(), 0, 0, 0, 0};
	if (!(mlx->buffer = malloc(sizeof(float *) * file->resolution.width)))
		return (2);
	ret = init_texture(mlx->mlx, &file->north);
	ret = ret ? ret : init_texture(mlx->mlx, &file->south);
	ret = ret ? ret : init_texture(mlx->mlx, &file->east);
	ret = ret ? ret : init_texture(mlx->mlx, &file->west);
	ret = ret ? ret : init_texture(mlx->mlx, &file->ceil);
	ret = ret ? ret : init_texture(mlx->mlx, &file->floor);
	ret = ret ? ret : init_sprites(mlx->mlx, file, player);
	return (ret);
}
