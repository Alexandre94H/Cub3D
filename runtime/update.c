/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/07 22:21:50 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#define XK_MISCELLANY
#include <X11/keysymdef.h>

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

void	ft_update_position(t_ajust ajust, t_mlx *mlx)
{
	if ((*mlx).input.forward)
	{
		(*mlx).player.position.x += ajust.direction.x / 50;
		(*mlx).player.position.y += ajust.direction.y / 50;
	}
	if ((*mlx).input.backward)
	{
		(*mlx).player.position.x -= ajust.direction.x / 50;
		(*mlx).player.position.y -= ajust.direction.y / 50;
	}
	if ((*mlx).input.turn_left)
	{
		(*mlx).player.position.x += ajust.direction.y / 50;
		(*mlx).player.position.y += -1 * ajust.direction.x / 50;
	}
	if ((*mlx).input.turn_right)
	{
		(*mlx).player.position.x -= ajust.direction.y / 50;
		(*mlx).player.position.y -= -1 * ajust.direction.x / 50;
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

	first = (mlx.settings.height - mlx.settings.height / distance) / 2;
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
	size_t	width;
	t_ajust	ajust;
	float	distance;

	width = 0;
	ajust = ft_ajust((*mlx).player);
	ft_update_position(ajust, mlx);
	while (width < (*mlx).settings.width)
	{
		distance = ft_distance(2 * width / (float)(*mlx).settings.width - 1, ajust, (*mlx).settings.map);
		ft_update_line(distance, width, *mlx);
		width++;
	}
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img, 0, 0);
	return (0);
}
