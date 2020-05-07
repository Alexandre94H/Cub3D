/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:39:07 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/07 20:52:25 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include <stdlib.h>
#include <X11/X.h>
#define XK_MISCELLANY
#include <X11/keysymdef.h>

int		ft_destroy(t_mlx *mlx)
{
	size_t	index;

	ft_putstr("Deletion of all variables.\n");
	index = 0;
	while ((*mlx).settings.map[index])
		free((*mlx).settings.map[index++]);
	free((*mlx).settings.map);
	mlx_mouse_show((*mlx).mlx, (*mlx).win);
	mlx_destroy_image((*mlx).mlx, (*mlx).img);
	mlx_destroy_window((*mlx).mlx, (*mlx).win);
	exit(0);
	return (0);
}

int		ft_mouse(int x, int y, t_mlx *mlx)
{
	t_position	middle;

	middle = (t_position) {
		 (*mlx).settings.width / 2,
		 (*mlx).settings.height / 2
	};
	if (x != middle.x || y != middle.y)
		mlx_mouse_move((*mlx).mlx, (*mlx).win, middle.x, middle.y);
	return (0);
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
	mlx_hook((*mlx).win, MotionNotify, PointerMotionMask, ft_mouse, mlx);
	mlx_loop_hook((*mlx).mlx, ft_update, mlx);
	mlx_mouse_hide((*mlx).mlx, (*mlx).win);
	ft_mouse(0, 0, mlx);
	mlx_hook((*mlx).win, KeyPress, KeyPressMask, ft_key_press, mlx);
	mlx_hook((*mlx).win, KeyRelease, KeyReleaseMask, ft_key_release, mlx);
	mlx_loop((*mlx).mlx);
}
