/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:39:07 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/28 20:43:21 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include <mlx.h>
#include <X11/X.h>
#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include "runtime.h"
#include "../main/cub3d.h"
#include "../get_next_line/get_next_line.h"

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
	else if (code == CAMERA_UP)
		(*mlx).input.camera_up = value;
	else if (code == CAMERA_DOWN)
		(*mlx).input.camera_down = value;
}

int		ft_key_press(int code, t_mlx *mlx)
{
	char	*filename;
	time_t	current;

	if (code == XK_Escape && code != XK_F2)
		ft_destroy(mlx);
	else if (code == XK_F2)
	{
		filename = ft_strdup("screenshot ");
		current = time(NULL);
		ft_stradd(&filename, asctime(localtime(&current)));
		(*mlx).settings.bitmap = filename;
		ft_putstr((*mlx).settings.bitmap, 1);
	}
	else
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
