/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:42:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/17 19:44:01 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "mlx1.h"

void	free_texture(void *mlx_ptr, t_texture *texture)
{
	if (texture->image)
		mlx_destroy_image(mlx_ptr, texture->image);
	else
		free(texture->data);
}

void	leave(t_runtime *runtime)
{
	unsigned short	index;

	index = 0;
	while (runtime->file.sprites[index])
	{
		free_texture(runtime->mlx.mlx, runtime->file.sprites[index]);
		free(runtime->file.sprites[index++]);
	}
	free(runtime->file.sprites);
	index = 0;
	while (runtime->player.sprites[index])
		free(runtime->player.sprites[index++]);
	free(runtime->player.sprites);
	index = 0;
	while (runtime->file.map[index])
		free(runtime->file.map[index++]);
	free(runtime->file.map);
	free(runtime->keys);
	free_texture(runtime->mlx.mlx, &runtime->file.north);
	free_texture(runtime->mlx.mlx, &runtime->file.south);
	free_texture(runtime->mlx.mlx, &runtime->file.east);
	free_texture(runtime->mlx.mlx, &runtime->file.west);
	free_texture(runtime->mlx.mlx, &runtime->file.floor);
	free_texture(runtime->mlx.mlx, &runtime->file.ceil);
	if (runtime->mlx.window)
		mlx_destroy_window(runtime->mlx.mlx, runtime->mlx.window);
}

void	stop(t_runtime *runtime)
{
	free(runtime->mlx.mlx);
	exit(0);
}

void	end(t_runtime *runtime)
{
	leave(runtime);
	stop(runtime);
}
