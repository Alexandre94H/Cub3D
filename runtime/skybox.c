/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 18:08:09 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/26 20:11:44 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	ft_set_skybox(t_mlx *mlx)
{
	size_t x;
	size_t y;
	size_t max;

	y = 0;
	max = (*mlx).settings.height * (*mlx).player.camera / 2 + 1;
	while (y < max)
	{
		x = 0;
		while (x < (*mlx).settings.width)
		{
			(*mlx).data[x + y * (*mlx).settings.width] = 255;
			x++;
		}
		y++;
	}
}