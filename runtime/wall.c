/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/20 18:03:27 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../engine/engine.h"

void	ft_wall_loop(t_mlx *mlx, t_calc calc, t_wall wall, size_t x)
{
	size_t	index;
	int		color;

	while (wall.y < wall.last)
	{
		index = TEXTURE_SIDE * (int)wall.texture_y + calc.texture_x;
		wall.texture_y += (float)TEXTURE_SIDE / wall.length;
		if (!calc.side)
			color = ft_get_color((*mlx).settings.textures.we, index);
		else if (calc.side == 1)
			color = ft_get_color((*mlx).settings.textures.no, index);
		else if (calc.side == 2)
			color = ft_get_color((*mlx).settings.textures.ea, index);
		else
			color = ft_get_color((*mlx).settings.textures.so, index);
		color = ft_fade(color, calc.distance);
		(*mlx).data[x + wall.y * (*mlx).settings.width] = color;
		wall.y++;
	}
}

void	ft_set_wall(t_mlx *mlx, t_ray ray)
{
	size_t	x;
	t_calc	calc;
	t_wall	wall;

	x = 0;
	while (x < (*mlx).settings.width)
	{
		calc = ft_distance(ray,
			2 * x / (float)(*mlx).settings.width - 1,
			(*mlx).player.position, (*mlx).settings.map);
		calc.texture_x *=  TEXTURE_SIDE;
		if (calc.side == 0 || calc.side == 3)
			calc.texture_x = TEXTURE_SIDE - calc.texture_x;
		wall = (t_wall){(*mlx).settings.height / calc.distance, 0, 0, 0};
		wall.y = -wall.length / 2 + (*mlx).settings.height / 2 * (*mlx).player.camera;
		if ((int)wall.y < 0)
			wall.y = 0;
		wall.last = wall.length / 2 + (*mlx).settings.height / 2 * (*mlx).player.camera;
		if (wall.last >= (*mlx).settings.height)
			wall.last = (*mlx).settings.height - 1;
		wall.texture_y = (wall.y - (*mlx).settings.height / 2 * (*mlx).player.camera + wall.length / 2) * (float)TEXTURE_SIDE / wall.length;
		ft_wall_loop(mlx, calc, wall, x);
		x++;
	}
}
