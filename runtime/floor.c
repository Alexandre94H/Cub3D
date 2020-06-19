/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/19 18:15:55 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	ft_set_floor(t_mlx *mlx, t_ray ray)
{
	size_t y;
	size_t x;

	y = (*mlx).settings.height * (*mlx).player.camera / 2 + 1;
	while (y < (*mlx).settings.height)
	{
		float rayDirX0 = ray.direction.x - ray.plane.x;
		float rayDirY0 = ray.direction.y - ray.plane.y;
		float rayDirX1 = ray.direction.x + ray.plane.x;
		float rayDirY1 = ray.direction.y + ray.plane.y;

		int p = y - (*mlx).settings.height / 2 * (*mlx).player.camera;

		float posZ = 0.5 * (*mlx).settings.height;

		float distance = posZ / p;

		float floorStepX = distance * (rayDirX1 - rayDirX0) / (*mlx).settings.width;
		float floorStepY = distance * (rayDirY1 - rayDirY0) / (*mlx).settings.width;

		float floorX = (*mlx).player.position.x + distance * rayDirX0;
		float floorY = (*mlx).player.position.y + distance * rayDirY0;

		x = 0;
		while (x < (*mlx).settings.width)
		{
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			int tx = (int)(64 * (floorX - cellX)) & (64 - 1);
			int ty = (int)(64 * (floorY - cellY)) & (64 - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			(*mlx).data[y * (*mlx).settings.width + x] = ft_fade(ft_get_color((*mlx).settings.textures.f, 64 * ty + tx), distance);
			//(*mlx).data[((*mlx).settings.height - y - 1) * (*mlx).settings.width + x] = ft_fade(ft_get_color((*mlx).settings.textures.f, 64 * ty + tx), distance);
			x++;
		}
		y++;
	}
}
