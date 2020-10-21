/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:25:15 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 20:19:23 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __USE_MISC
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <mlx.h>
#include "../mlx_full.h"
#include "update.h"

void	update_window(t_runtime *runtime)
{
	t_ray			ray;

	runtime->mlx.image = mlx_new_image(runtime->mlx.mlx,
		runtime->file.resolution.width, runtime->file.resolution.height);
	runtime->mlx.data = image_data(runtime->mlx.image,
		runtime->file.resolution.width);
	ray = (t_ray){{sin(runtime->player.degree * M_PI / 180),
		-1 * cos(runtime->player.degree * M_PI / 180)},
		{cos(runtime->player.degree * M_PI / 180) * FOV / 100,
		sin(runtime->player.degree * M_PI / 180) * FOV / 100}, 0};
	update_floor(runtime, ray);
	update_wall(runtime, ray);
	update_sprite(runtime, ray);
	if (runtime->mlx.window)
		mlx_put_image_to_window(runtime->mlx.mlx,
			runtime->mlx.window, runtime->mlx.image, 0, 0);
	runtime->player.updated = true;
}

void	update_key(t_runtime *runtime)
{
	update_keys(runtime);
	if (runtime->save)
	{
		bitmap("save.bmp", runtime);
		runtime->save = false;
	}
	mlx_destroy_image(runtime->mlx.mlx, runtime->mlx.image);
	if (runtime->end)
		end(runtime, 0);
}

void	update_z(t_runtime *runtime)
{
	float	amount;

	if (!runtime->player.position.z)
		return ;
	amount = (float)5 / MAX_FPS;
	if (fabs(runtime->player.position.z) - amount < 0)
		amount = runtime->player.position.z;
	else if (runtime->player.position.z < 0)
		amount *= -1;
	runtime->player.position.z -= amount;
}

int		update(t_runtime *runtime)
{
	static bool		editing;
	static clock_t	last_frame;

	if ((runtime->player.updated && runtime->player.position.z == 0) || editing)
		return (1);
	if (last_frame && 1000000 / MAX_FPS > clock() - last_frame)
		return (2);
	editing = true;
	last_frame = clock();
	update_window(runtime);
	update_z(runtime);
	update_key(runtime);
	editing = false;
	return (0);
}
