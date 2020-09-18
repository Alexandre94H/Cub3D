/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/20 18:00:35 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	ft_floor_loop(t_mlx *mlx, t_floor floor, size_t y)
{
	size_t	x;

	x = 0;
	while (x < (*mlx).settings.width)
	{
		(*mlx).data[x + y * (*mlx).settings.width] = ft_fade(ft_get_color((*mlx).settings.textures.f, ((int)(TEXTURE_SIDE * floor.floorx) & (TEXTURE_SIDE - 1)) + ((int)(TEXTURE_SIDE * floor.floory) & (TEXTURE_SIDE - 1)) * TEXTURE_SIDE), floor.distance);
		floor.floorx += floor.stepx;
		floor.floory += floor.stepy;
		x++;
	}
}

void	ft_set_floor(t_mlx *mlx, t_ray ray)
{
	size_t	y;
	t_floor	floor;

	y = (*mlx).settings.height * (*mlx).player.camera / 2 + 1;
	while (y < (*mlx).settings.height)
	{
		floor = (t_floor){0.5 * ((*mlx).settings.height) / (y - (*mlx).settings.height * (*mlx).player.camera / 2), 0, 0, 0, 0};
		floor.floorx = ((*mlx).player.position.x - (int)(*mlx).player.position.x) + floor.distance * (ray.direction.x - ray.plane.x);
		floor.floory = ((*mlx).player.position.y - (int)(*mlx).player.position.y) + floor.distance * (ray.direction.y - ray.plane.y);
		floor.stepx = floor.distance * (ray.plane.x * 2) / (*mlx).settings.width;
		floor.stepy = floor.distance * (ray.plane.y * 2) / (*mlx).settings.width;
		ft_floor_loop(mlx, floor, y);
		y++;
	}
}
