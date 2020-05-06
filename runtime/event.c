/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:39:07 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/06 23:39:24 by ahallain         ###   ########.fr       */
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
	mlx_destroy_image((*mlx).mlx, (*mlx).img);
	mlx_destroy_window((*mlx).mlx, (*mlx).win);
	exit(0);
	return (0);
}

int		ft_key(int code, t_mlx *mlx)
{
	t_ajust	ajust;

	if (code == XK_Escape)
	{
		ft_destroy(mlx);
		return (0);
	}
	if (code == LEFT)
		(*mlx).player.degree = ((int)(*mlx).player.degree - 5 + 360) % 360;
	else if (code == RIGHT)
		(*mlx).player.degree = ((int)(*mlx).player.degree + 5) % 360;
	else {
		ajust = ft_ajust((*mlx).player);
		if (code == FORWARD) {
			(*mlx).player.position.x += ajust.direction.x;
			(*mlx).player.position.y += ajust.direction.y;
		} else if (code == BACKWARD) {
			(*mlx).player.position.x -= ajust.direction.x;
			(*mlx).player.position.y -= ajust.direction.y;
		} else
			return (0);
	}
	ft_update(mlx);
	return (0);
}

void	ft_detect(t_mlx *mlx)
{
	mlx_hook((*mlx).win, KeyPress, KeyPressMask, ft_key, mlx);
	mlx_hook((*mlx).win, MapNotify, StructureNotifyMask, ft_update, mlx);
	mlx_hook((*mlx).win, DestroyNotify, StructureNotifyMask, ft_destroy, mlx);
	mlx_loop((*mlx).mlx);
}
