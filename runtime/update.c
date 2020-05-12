/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/12 09:26:19 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include "../raycaster/raycaster.h"
#define __USE_MISC
#include <math.h>
#include <time.h>

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
	direction = (t_position) {
		sin((*mlx).player.degree * M_PI / 180),
		-1 * cos((*mlx).player.degree * M_PI / 180)
	};
	(*mlx).playerold = (*mlx).player;
	if ((*mlx).input.forward)
	{
		(*mlx).player.position.x += direction.x / 20;
		(*mlx).player.position.y += direction.y / 20;
	}
	if ((*mlx).input.backward)
	{
		(*mlx).player.position.x -= direction.x / 20;
		(*mlx).player.position.y -= direction.y / 20;
	}
	if ((*mlx).input.turn_left)
	{
		(*mlx).player.position.x += direction.y / 20;
		(*mlx).player.position.y += -1 * direction.x / 20;
	}
	if ((*mlx).input.turn_right)
	{
		(*mlx).player.position.x -= direction.y / 20;
		(*mlx).player.position.y -= -1 * direction.x / 20;
	}
	if ((*mlx).input.rotate_left)
		(*mlx).player.degree = (*mlx).player.degree - 1;
	if ((*mlx).input.rotate_right)
		(*mlx).player.degree = (*mlx).player.degree + 1;
}

void	ft_update_line(float distance, size_t width, t_mlx mlx)
{
	int		color;
	size_t	first;
	size_t	height;

	first = (mlx.settings.height - mlx.settings.height / distance * 3 / 4) / 2;
	height = 0;
	while (height < mlx.settings.height)
	{
		if ((long)first < 0)
			first = 0;
		color = 0;
		if (height < first)
			color = mlx.settings.color.c;
		else if (height > mlx.settings.height - first)
			color = mlx.settings.color.f;
		mlx.data[height * mlx.settings.width + width] = color;
		height++;
	}
}

int		ft_update(t_mlx *mlx)
{
	size_t			width;
	bool			verify;
	t_ray			ray;
	float			distance;
	static long int	last_frame; 

	if (last_frame && (long)(1000000 / FPS) > clock() - last_frame)
		return (1);
	last_frame = clock();
	width = 0;
	verify = (*mlx).playerold.initiate;
	ray = ft_init_ray((*mlx).player.degree);
	ft_update_position(mlx, ray.direction);
	if (verify
		&& (*mlx).playerold.degree == (*mlx).player.degree
		&& (*mlx).playerold.position.x == (*mlx).player.position.x
		&& (*mlx).playerold.position.y == (*mlx).player.position.y)
			return (0);
	while (width < (*mlx).settings.width)
	{
		distance = ft_distance(ray, 2 * width / (float)(*mlx).settings.width - 1, (*mlx).player.position, (*mlx).settings.map);
		ft_update_line(distance, width, *mlx);
		width++;
	}
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img, 0, 0);
	return (0);
}
