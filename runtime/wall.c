/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/19 17:33:01 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../engine/engine.h"

void	ft_wall_loop(t_mlx *mlx, t_wall *wall, t_calc calc, size_t x)
{
	size_t	index;
	int		color;

	if ((*wall).y < (*wall).first || (*wall).y >= (*wall).last)
		return ;
	index = 64 * (int)(*wall).texture_y + calc.texture_x * 64;
	(*wall).texture_y += (float)64 / (*wall).length;
	if (!calc.side)
		color = ft_get_color((*mlx).settings.textures.we, index);
	else if (calc.side == 1)
		color = ft_get_color((*mlx).settings.textures.no, index);
	else if (calc.side == 2)
		color = ft_get_color((*mlx).settings.textures.ea, index);
	else
		color = ft_get_color((*mlx).settings.textures.so, index);
	color = ft_fade(color, calc.distance);
	(*mlx).data[x + (*wall).y * (*mlx).settings.width] = color;
}

void	ft_set_wall_line(t_mlx *mlx, t_calc calc, size_t x)
{
	t_wall	wall;

	wall = (t_wall){(*mlx).settings.height / calc.distance, 0, 0, 0, 0};
	wall.first = -wall.length / 2 + (*mlx).settings.height / 2 * (*mlx).player.camera;
	if ((int)wall.first < 0)
		wall.first = 0;
	wall.last = wall.length / 2 + (*mlx).settings.height / 2 * (*mlx).player.camera;
	if (wall.last >= (*mlx).settings.height)
		wall.last = (*mlx).settings.height - 1;
	wall.texture_y = (wall.first - (*mlx).settings.height / 2 * (*mlx).player.camera + wall.length / 2)
		* (float)64 / wall.length;
	while (wall.y < (*mlx).settings.height)
	{
		ft_wall_loop(mlx, &wall, calc, x);
		wall.y++;
	}
}

void	ft_set_wall(t_mlx *mlx, t_ray ray)
{
	size_t			x;
	t_calc			calc;

	x = 0;
	while (x < (*mlx).settings.width)
	{
		calc = ft_distance(ray,
			2 * x / (float)(*mlx).settings.width - 1,
			(*mlx).player.position, (*mlx).settings.map);
		ft_set_wall_line(mlx, calc, x);
		x++;
	}
}
