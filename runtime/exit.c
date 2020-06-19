/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 05:37:09 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/19 05:41:19 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "runtime.h"
#include "../main/cub3d.h"

void	ft_destroy_xpm(void *mlx_ptr, t_xpm *xpm)
{
	if ((*xpm).initiate)
		mlx_destroy_image(mlx_ptr, (*xpm).img);
	else
		free((*xpm).data);
}

int		ft_destroy(t_mlx *mlx)
{
	size_t	index;

	ft_putstr("Deletion of all variables.\n");
	index = 0;
	while ((*mlx).settings.map[index])
		free((*mlx).settings.map[index++]);
	free((*mlx).settings.map);
	ft_destroy_xpm((*mlx).mlx, &(*mlx).settings.textures.no);
	ft_destroy_xpm((*mlx).mlx, &(*mlx).settings.textures.so);
	ft_destroy_xpm((*mlx).mlx, &(*mlx).settings.textures.we);
	ft_destroy_xpm((*mlx).mlx, &(*mlx).settings.textures.ea);
	ft_destroy_xpm((*mlx).mlx, &(*mlx).settings.textures.s);
	ft_destroy_xpm((*mlx).mlx, &(*mlx).settings.textures.c);
	ft_destroy_xpm((*mlx).mlx, &(*mlx).settings.textures.f);
	if (!(*mlx).settings.save)
		mlx_destroy_window((*mlx).mlx, (*mlx).win);
	exit(0);
	return (0);
}