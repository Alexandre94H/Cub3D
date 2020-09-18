/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:16:20 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/20 18:36:52 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <mlx.h>
#include "../engine/engine.h"

int		ft_fade(int color, float divide)
{
	int	fade;

	if (divide < 1)
		return (color);
	fade = ((255 << 16 & color) >> 16) / divide;
	fade <<= 8;
	fade += ((255 << 8 & color) >> 8) / divide;
	fade <<= 8;
	fade += (255 & color) / divide;
	return (fade);
}

int		ft_get_color(t_xpm xpm, size_t index)
{
	if (xpm.initiate)
		return (xpm.data[index]);
	return (xpm.data[0]);
}

t_ray	ft_init_update(t_mlx *mlx)
{
	t_ray			ray;

	ray = ft_init_ray((*mlx).player.degree);
	ft_update_input(mlx, ray.direction);
	if ((*mlx).player.camera > 2)
		(*mlx).player.camera = 2;
	if ((*mlx).player.camera < 0)
		(*mlx).player.camera = 0;
	if (!(*mlx).settings.save)
	{
		(*mlx).img = mlx_new_image((*mlx).mlx, (*mlx).settings.width, (*mlx).settings.height);
		(*mlx).data = ft_data((*mlx).img, (*mlx).settings.width);
	}
	return ray;
}

int		ft_update(t_mlx *mlx)
{
	t_ray			ray;
	static long int	last_frame;

	if (last_frame && !(*mlx).settings.bitmap && !ft_check_input(*mlx))
		return (1);
	if (last_frame && (long)(1000000 / FPS) > clock() - last_frame)
		return (2);
	last_frame = clock();
	ray = ft_init_update(mlx);
	ft_set_floor(mlx, ray);
	ft_set_skybox(mlx);
	ft_set_wall(mlx, ray);
	if ((*mlx).settings.bitmap)
		ft_bitmap(mlx);
	if (!(*mlx).settings.save)
	{
		mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img, 0, 0);
		mlx_destroy_image((*mlx).mlx, (*mlx).img);
	}
	return (0);
}
