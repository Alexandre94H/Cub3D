/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:42:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/08 20:46:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "mlx1.h"

void	free_texture(void	*mlx_ptr, t_texture *texture)
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
		index++;
	}
	free_texture(runtime->mlx.mlx, &runtime->file.north);
	free_texture(runtime->mlx.mlx, &runtime->file.south);
	free_texture(runtime->mlx.mlx, &runtime->file.east);
	free_texture(runtime->mlx.mlx, &runtime->file.west);
	free_texture(runtime->mlx.mlx, &runtime->file.floor);
	free_texture(runtime->mlx.mlx, &runtime->file.ceil);
	free(runtime->file.map);
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