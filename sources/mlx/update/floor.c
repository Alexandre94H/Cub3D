/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:32:39 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 19:22:50 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../mlx_full.h"
#include "update.h"

#include "../../library.h"

void		floor_color(t_runtime *runtime, bool is_floor, t_position floor,
	t_resolution position)
{
	int	color;

	if (is_floor)
		color = runtime->file.floor.data[runtime->file.floor.resolution.width * (unsigned short)(runtime->file.floor.resolution.height * floor.y) + (unsigned short)(runtime->file.floor.resolution.width * floor.x)];
	else
		color = runtime->file.ceil.data[runtime->file.ceil.resolution.width * (unsigned short)(runtime->file.ceil.resolution.height * floor.y) + (unsigned short)(runtime->file.ceil.resolution.width * floor.x)];
	runtime->mlx.data[position.height * runtime->file.resolution.width + position.width] = color;
}

t_position	floor_init(t_runtime *runtime, t_ray ray, unsigned short y,
	t_position *step)
{
	t_position		ray_dir;
	t_position		ray_dir1;
	float			row_distance;
	t_position		floor;

	ray_dir = (t_position){ray.direction.x - ray.plan.x,
		ray.direction.y - ray.plan.y};
	ray_dir1 = (t_position){ray.direction.x + ray.plan.x,
		ray.direction.y + ray.plan.y};
	if (y > runtime->file.resolution.height / 2	+ runtime->player.pitch * 200)
		row_distance = (0.5 * runtime->file.resolution.height + runtime->player.position.z * 200) / (float)(y - runtime->file.resolution.height / 2 - runtime->player.pitch * 200);
	else
		row_distance = (0.5 * runtime->file.resolution.height - runtime->player.position.z * 200) / (float)(runtime->file.resolution.height / 2 - y + runtime->player.pitch * 200);
	floor = (t_position){runtime->player.position.x + row_distance *
		ray_dir.x, runtime->player.position.y + row_distance * ray_dir.y};
	*step = (t_position){row_distance * (ray_dir1.x - ray_dir.x) /
		runtime->file.resolution.width, row_distance * (ray_dir1.y -
		ray_dir.y) / runtime->file.resolution.width};
	return (floor);
}

void		update_floor(t_runtime *runtime, t_ray ray)
{
	unsigned short	x;
	unsigned short	y;
	bool			is_floor;
	t_position		floor;
	t_position		step;

	y = 0;
	while (y < runtime->file.resolution.height)
	{
		is_floor = y > runtime->file.resolution.height / 2
			+ runtime->player.pitch * 200;
		floor = floor_init(runtime, ray, y, &step);
		x = 0;
		while (x < runtime->file.resolution.width)
		{
			floor.x -= (int)floor.x;
			floor.y -= (int)floor.y;
			if (floor.x < 0)
				floor.x += 1;
			if (floor.y < 0)
				floor.y += 1;
			floor_color(runtime, is_floor, floor, (t_resolution){x, y});
			floor.x += step.x;
			floor.y += step.y;
			x++;
		}
		y++;
	}
}
