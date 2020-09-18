/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/20 05:03:01 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

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
	if ((*mlx).input.camera_up)
		(*mlx).player.camera += 2.0 / FPS;
	if ((*mlx).input.camera_down)
		(*mlx).player.camera -= 2.0 / FPS;
}

bool	ft_check_input(t_mlx mlx)
{
	if (mlx.input.forward)
		return (true);
	if (mlx.input.backward)
		return (true);
	if (mlx.input.turn_left)
		return (true);
	if (mlx.input.turn_right)
		return (true);
	if (mlx.input.rotate_left)
		return (true);
	if (mlx.input.rotate_right)
		return (true);
	if (mlx.input.camera_up)
		return (true);
	if (mlx.input.camera_down)
		return (true);
	return (false);
}
