/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:42:04 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 21:07:21 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "mlx/mlx1.h"

void	safe_free(void *item)
{
	if (!item)
		free(item);
}

void	free_texture(void *mlx_ptr, t_texture *texture)
{
	if (!texture || !texture->data)
		return ;
	if (mlx_ptr && texture->image)
		mlx_destroy_image(mlx_ptr, texture->image);
	else
		safe_free(texture->data);
}

void	free_list(void	**list)
{
	unsigned short	index;

	if (!list)
		return ;
	index = 0;
	(void)index;
	while (list[index])
		safe_free(list[index]);
	safe_free(list);
}

unsigned char	end(t_runtime *runtime, unsigned char exit_code)
{

	free_list((void **)runtime->file.map);
	free_list((void **)runtime->file.sprites);
	free_list((void **)runtime->player.sprites);
	free_texture(runtime->mlx.mlx, &runtime->file.north);
	free_texture(runtime->mlx.mlx, &runtime->file.south);
	free_texture(runtime->mlx.mlx, &runtime->file.east);
	free_texture(runtime->mlx.mlx, &runtime->file.west);
	free_texture(runtime->mlx.mlx, &runtime->file.floor);
	free_texture(runtime->mlx.mlx, &runtime->file.ceil);
	safe_free((void **)runtime->keys);
	safe_free((void **)runtime->mlx.buffer);
	if (runtime->mlx.window)
		mlx_destroy_window(runtime->mlx.mlx, runtime->mlx.window);
	safe_free(runtime->mlx.mlx);
	return (exit_code);
}
