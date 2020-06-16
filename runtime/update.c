/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/16 21:46:05 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_MISCELLANY
#include <X11/keysymdef.h>
#define __USE_MISC
#include <math.h>
#include <time.h>
#include <mlx.h>
#include "runtime.h"
#include "../engine/engine.h"

void	ft_update_position(t_mlx *mlx, float addx, float addy)
{
	if ((*mlx).settings.map[(int)(*mlx).player.position.y]
		[(int)((*mlx).player.position.x + addx)] != '1')
		(*mlx).player.position.x += addx;
	if ((*mlx).settings.map[(int)((*mlx).player.position.y + addy)]
		[(int)(*mlx).player.position.x] != '1')
		(*mlx).player.position.y += addy;
}

void	ft_update_input(t_mlx *mlx, t_position direction)
{
	if ((*mlx).input.forward)
		ft_update_position(mlx, direction.x * 2.0 / FPS,
			direction.y * 2.0 / FPS);
	if ((*mlx).input.backward)
		ft_update_position(mlx, direction.x * -2.0 / FPS,
			direction.y * -2.0 / FPS);
	if ((*mlx).input.turn_left)
		ft_update_position(mlx, direction.y * 2.0 / FPS,
			direction.x * -2.0 / FPS);
	if ((*mlx).input.turn_right)
		ft_update_position(mlx, direction.y * -2.0 / FPS,
			direction.x * 2.0 / FPS);
	if ((*mlx).input.rotate_left)
		(*mlx).player.degree = (*mlx).player.degree - 100.0 / 2.0 / FPS;
	if ((*mlx).input.rotate_right)
		(*mlx).player.degree = (*mlx).player.degree + 100.0 / 2.0 / FPS;
}

void	ft_update_loop(t_mlx *mlx, t_loop *loop, t_calc calc, size_t x)
{
	size_t	index;
	int		color;

	if ((*loop).y < (*loop).first)
		color = (*mlx).settings.colors.c;
	else if ((*loop).y >= (*loop).last)
		color = (*mlx).settings.colors.f;
	else
	{
		index = 64 * (int)(*loop).texture_y + calc.texture_x * 64;
		(*loop).texture_y += (float)64 / (*loop).length;
		if (!calc.side)
			color = (*mlx).settings.textures.we.data[index];
		else if (calc.side == 1)
			color = (*mlx).settings.textures.no.data[index];
		else if (calc.side == 2)
			color = (*mlx).settings.textures.ea.data[index];
		else
			color = (*mlx).settings.textures.so.data[index];
	}
	(*mlx).data[x + (*loop).y * (*mlx).settings.width] = color;
}

void	ft_update_line(t_mlx *mlx, t_calc calc, size_t x)
{
	t_loop	loop;

	loop = (t_loop){(*mlx).settings.height / calc.distance * 3 / 4, 0, 0, 0, 0};
	loop.first = -loop.length / 2 + (*mlx).settings.height / 2;
	if ((int)loop.first < 0)
		loop.first = 0;
	loop.last = loop.length / 2 + (*mlx).settings.height / 2;
	loop.texture_y = (loop.first - (*mlx).settings.height / 2 + loop.length / 2)
		* (float)64 / loop.length;
	while (loop.y < (*mlx).settings.height)
	{
		ft_update_loop(mlx, &loop, calc, x);
		loop.y++;
	}
}

int		ft_update(t_mlx *mlx)
{
	size_t			x;
	t_ray			ray;
	t_calc			calc;
	static long int	last_frame;

	if (last_frame && (long)(1000000 / FPS) > clock() - last_frame)
		return (1);
	last_frame = clock();
	x = 0;
	ray = ft_init_ray((*mlx).player.degree);
	ft_update_input(mlx, ray.direction);
	while (x < (*mlx).settings.width)
	{
		calc = ft_distance(ray,
			2 * x / (float)(*mlx).settings.width - 1,
			(*mlx).player.position, (*mlx).settings.map);
		ft_update_line(mlx, calc, x);
		x++;
	}
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img, 0, 0);
	return (0);
}
