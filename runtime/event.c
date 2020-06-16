/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:39:07 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/16 21:17:42 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <X11/X.h>
#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include "runtime.h"
#include "../main/cub3d.h"

int		ft_destroy(t_mlx *mlx)
{
	size_t	index;

	ft_putstr("Deletion of all variables.\n");
	index = 0;
	while ((*mlx).settings.map[index])
		free((*mlx).settings.map[index++]);
	free((*mlx).settings.map);
	mlx_destroy_image((*mlx).mlx, (*mlx).settings.textures.no.img);
	mlx_destroy_image((*mlx).mlx, (*mlx).settings.textures.so.img);
	mlx_destroy_image((*mlx).mlx, (*mlx).settings.textures.we.img);
	mlx_destroy_image((*mlx).mlx, (*mlx).settings.textures.ea.img);
	mlx_destroy_image((*mlx).mlx, (*mlx).settings.textures.s.img);
	mlx_destroy_image((*mlx).mlx, (*mlx).img);
	mlx_destroy_window((*mlx).mlx, (*mlx).win);
	exit(0);
	return (0);
}

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

int		ft_key_press(int code, t_mlx *mlx)
{
	if (code == XK_Escape)
	{
		ft_destroy(mlx);
		return (0);
	}
	ft_update_key(code, 1, mlx);
	return (0);
}

int		ft_key_release(int code, t_mlx *mlx)
{
	ft_update_key(code, 0, mlx);
	return (0);
}

void	ft_detect(t_mlx *mlx)
{
	mlx_hook((*mlx).win, DestroyNotify, StructureNotifyMask, ft_destroy, mlx);
	mlx_hook((*mlx).win, KeyPress, KeyPressMask, ft_key_press, mlx);
	mlx_hook((*mlx).win, KeyRelease, KeyReleaseMask, ft_key_release, mlx);
	mlx_loop_hook((*mlx).mlx, ft_update, mlx);
	mlx_loop((*mlx).mlx);
}
