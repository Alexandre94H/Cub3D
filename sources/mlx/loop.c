/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:51:26 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/20 19:14:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include <X11/X.h>
#include <stdbool.h>
#include <mlx.h>
#include "mlx_full.h"

int		destroy(t_runtime *runtime)
{
	end(runtime);
	return (0);
}

int		mouse(int x, int y, t_runtime *runtime)
{
	t_resolution	middle;

	middle = (t_resolution){runtime->file.resolution.width / 2,
		runtime->file.resolution.height / 2};
	if (x == middle.width && y == middle.height)
		return (1);
	mlx_mouse_move(runtime->mlx.mlx, runtime->mlx.window,
		middle.width, middle.height);
	if (x < middle.width)
		runtime->player.degree -= 0.5;
	else if (x > middle.width)
		runtime->player.degree += 0.5;
	while (runtime->player.degree < 0)
		runtime->player.degree += 360;
	while (runtime->player.degree > 360)
		runtime->player.degree -= 360;
	if (y < middle.height)
		runtime->player.pitch += 0.01;
	else if (y > middle.height)
		runtime->player.pitch -= 0.01;
	if (runtime->player.pitch < -1)
		runtime->player.pitch = -1;
	if (runtime->player.pitch > 1)
		runtime->player.pitch = 1;
	return ((runtime->player.updated = false));
}

int		create(t_runtime *runtime)
{
	runtime->player.updated = false;
	return (0);
}

void	hook(t_runtime *runtime)
{
	if (BONUS)
	{
		mlx_hook(runtime->mlx.window, MotionNotify, PointerMotionMask, mouse,
			runtime);
		mlx_mouse_hide(runtime->mlx.mlx, runtime->mlx.window);
		mlx_mouse_move(runtime->mlx.mlx, runtime->mlx.window,
			runtime->file.resolution.width / 2,
			runtime->file.resolution.height / 2);
	}
	mlx_hook(runtime->mlx.window, DestroyNotify, StructureNotifyMask,
		destroy, runtime);
	mlx_hook(runtime->mlx.window, FocusIn, FocusChangeMask, create,
		runtime);
	mlx_hook(runtime->mlx.window, KeyPress, KeyPressMask, press, runtime);
	mlx_hook(runtime->mlx.window, KeyPress, KeyPressMask, press, runtime);
	mlx_hook(runtime->mlx.window, KeyRelease, KeyReleaseMask, release,
		runtime);
	mlx_loop_hook(runtime->mlx.mlx, update, runtime);
}

void	loop(char *name, t_runtime runtime, bool save)
{
	mlx_do_key_autorepeatoff(runtime.mlx.mlx);
	if (save)
	{
		press(XK_F2, &runtime);
		press(XK_Escape, &runtime);
	}
	else
	{
		check_resolution(runtime.mlx.mlx,
			&runtime.file.resolution);
		runtime.mlx.window = mlx_new_window(runtime.mlx.mlx,
			runtime.file.resolution.width, runtime.file.resolution.height,
				name);
		hook(&runtime);
		mlx_loop(runtime.mlx.mlx);
	}
	update(&runtime);
}
