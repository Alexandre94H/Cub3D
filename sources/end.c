/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:42:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 22:23:02 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "mlx/mlx1.h"

void			free_texture(void *mlx_ptr, t_texture *texture)
{
	if (!texture)
		return ;
	if (mlx_ptr && texture->image)
		mlx_destroy_image(mlx_ptr, texture->image);
	else
		free(texture->data);
}

void			free_list(void **list)
{
	unsigned short	index;

	if (!list)
		return ;
	index = 0;
	while (list[index])
		free(list[index++]);
	free(list);
}

void			free_mlx(t_runtime *runtime)
{
	if (runtime->mlx.window)
		mlx_destroy_window(runtime->mlx.mlx, runtime->mlx.window);
	free(runtime->mlx.mlx);
}

unsigned char	end(t_runtime *runtime, unsigned char exit_code)
{
	unsigned short	index;

	if (runtime->file.sprites)
	{
		index = 0;
		while (runtime->file.sprites[index])
		{
			free_texture(runtime->mlx.mlx, runtime->file.sprites[index]);
			free(runtime->file.sprites[index++]);
		}
		free(runtime->file.sprites);
	}
	free_list((void **)runtime->player.sprites);
	free_list((void **)runtime->file.map);
	free_texture(runtime->mlx.mlx, &runtime->file.north);
	free_texture(runtime->mlx.mlx, &runtime->file.south);
	free_texture(runtime->mlx.mlx, &runtime->file.east);
	free_texture(runtime->mlx.mlx, &runtime->file.west);
	free_texture(runtime->mlx.mlx, &runtime->file.floor);
	free_texture(runtime->mlx.mlx, &runtime->file.ceil);
	free(runtime->keys);
	free(runtime->mlx.buffer);
	free_mlx(runtime);
	exit(exit_code);
	return (exit_code);
}
