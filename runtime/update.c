/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/14 17:21:00 by ahallain         ###   ########.fr       */
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

void	ft_update_key(int code, int value, t_mlx *mlx)
{
	if (code == FORWARD)
		(*mlx).input.forward = value;
	else if (code == BACKWARD)
		(*mlx).input.backward = value;
	else if (code == TURN_LEFT)
		(*mlx).input.turn_left = value;
	else if (code == TURN_RIGHT)
		(*mlx).input.turn_right = value;
	else if (code == XK_Left)
		(*mlx).input.rotate_left = value;
	else if (code == XK_Right)
		(*mlx).input.rotate_right = value;
}

void	ft_update_position(t_mlx *mlx, t_position direction)
{
	if ((*mlx).input.forward)
	{
		(*mlx).player.position.x += direction.x * 2.0 / FPS;
		(*mlx).player.position.y += direction.y * 2.0 / FPS;
	}
	if ((*mlx).input.backward)
	{
		(*mlx).player.position.x -= direction.x * 2.0 / FPS;
		(*mlx).player.position.y -= direction.y * 2.0 / FPS;
	}
	if ((*mlx).input.turn_left)
	{
		(*mlx).player.position.x += direction.y * 2.0 / FPS;
		(*mlx).player.position.y += -1 * direction.x * 2.0 / FPS;
	}
	if ((*mlx).input.turn_right)
	{
		(*mlx).player.position.x -= direction.y * 2.0 / FPS;
		(*mlx).player.position.y -= -1 * direction.x * 2.0 / FPS;
	}
	if ((*mlx).input.rotate_left)
		(*mlx).player.degree = (*mlx).player.degree - 100.0 / 2.0 / FPS;
	if ((*mlx).input.rotate_right)
		(*mlx).player.degree = (*mlx).player.degree + 100.0 / 2.0 / FPS;
}

void	ft_update_line(t_calc calc, size_t width, t_mlx mlx)
{
	int		color;
	int		index;
	size_t	first;
	size_t	height;

	first = (mlx.settings.height - mlx.settings.height / calc.distance * 3 / 4) / 2;
	height = 0;
	while (height < mlx.settings.height)
	{
		if ((long)first < 0)
			first = 0;
		if (height < first)
			color = mlx.settings.colors.c;
		else if (height > mlx.settings.height - first - 1)
			color = mlx.settings.colors.f;
		else
		{
			index = (int) (calc.texture_x * 64 + ((height - first) * 64 / (mlx.settings.height - first * 2)) * 64);
			if (!calc.side)
				color = mlx.settings.textures.we.data[index];
			else if (calc.side == 1)
				color = mlx.settings.textures.no.data[index];
			else if (calc.side == 2)
				color = mlx.settings.textures.ea.data[index];
			else
				color = mlx.settings.textures.so.data[index];
		}
		mlx.data[height * mlx.settings.width + width] = color;
		height++;
	}
}

int		ft_update(t_mlx *mlx)
{
	size_t			width;
	t_ray			ray;
	t_calc			calc;
	static long int	last_frame;

	if (last_frame && (long)(1000000 / FPS) > clock() - last_frame)
		return (1);
	last_frame = clock();
	width = 0;
	ray = ft_init_ray((*mlx).player.degree);
	ft_update_position(mlx, ray.direction);
	while (width < (*mlx).settings.width)
	{
		calc = ft_distance(ray,
			2 * width / (float)(*mlx).settings.width - 1,
			(*mlx).player.position, (*mlx).settings.map);
		ft_update_line(calc, width, *mlx);
		width++;
	}
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img, 0, 0);
	return (0);
}
