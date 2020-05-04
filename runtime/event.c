/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:39:07 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/04 18:31:09 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include <stdlib.h>
#include <X11/X.h>
#define XK_MISCELLANY
#include <X11/keysymdef.h>

t_mlx	g_mlx;

int		ft_destroy(void)
{
	size_t	index;

	ft_putstr("Deletion of all variables.\n");
	index = 0;
	while (g_mlx.settings.map[index])
		free(g_mlx.settings.map[index++]);
	free(g_mlx.settings.map);
	mlx_destroy_image(g_mlx.mlx, g_mlx.img);
	exit(0);
	return (0);
}

int		ft_key(int code)
{
	if (code == XK_Escape)
		ft_destroy();
	ft_update(g_mlx);
	ft_putstr("key: ");
	ft_putnbr(code);
	ft_putchar('\n');
	return (0);
}

void	ft_detect(t_mlx mlx)
{
	g_mlx = mlx;
	mlx_hook(g_mlx.win, KeyPress, KeyPressMask, ft_key, 0);
	mlx_hook(g_mlx.win, DestroyNotify, StructureNotifyMask, ft_destroy, 0);
	mlx_loop(g_mlx.mlx);
}
