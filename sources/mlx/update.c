/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:01:06 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/08 21:14:06 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __USE_MISC
#include <math.h>
#include <mlx.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "mlx_full.h"

void	update_floor(t_runtime *runtime, t_ray ray)
{
	unsigned short	x;
	unsigned short	y;
	float			distance;
	t_position		floor;
	t_position		texture;
	int				color;

	texture = (t_position) {0, 0};
	y = 0;
	while (y < runtime->file.resolution.height / 2)
	{
		distance = (float)runtime->file.resolution.height / 2 / y;
		floor = (t_position) {runtime->player.position.x + distance * (ray.direction.x - ray.plan.x), runtime->player.position.y + distance * (ray.direction.y - ray.plan.y)};

		x = 0;
		while (x < runtime->file.resolution.width)
		{
			texture.x = floor.x - (short)floor.x;
			texture.y = floor.y - (short)floor.y;
			
			color = runtime->file.floor.data[runtime->file.floor.resolution.width * (short)(texture.y * (runtime->file.floor.resolution.height - 1)) + (short)(texture.x * (runtime->file.floor.resolution.width - 1))];
			runtime->mlx.data[(y + runtime->file.resolution.height / 2) * runtime->file.resolution.width + x] = color;
			
			color = runtime->file.ceil.data[runtime->file.ceil.resolution.width * (short)(texture.y * (runtime->file.ceil.resolution.height - 1)) + (short)(texture.x * (runtime->file.ceil.resolution.width - 1))];
			runtime->mlx.data[(runtime->file.resolution.height / 2 - y) * runtime->file.resolution.width + x] = color;

			floor.x += 2 * distance * ray.plan.x / runtime->file.resolution.width;
			floor.y += 2 * distance * ray.plan.y / runtime->file.resolution.width;
			x++;
		}
		y++;
	}
}

void update_wall(t_runtime *runtime, t_ray ray)
{
	unsigned short	x;
	float			cameraX;
	t_position		direction;
	t_resolution	map;
	t_position		side;
	unsigned short	lineHeight;
	t_resolution	draw;

	x = 0;
	while (x < runtime->file.resolution.width)
	{
		cameraX = 2 * x / (float)runtime->file.resolution.width - 1;
		direction = (t_position){ray.direction.x + ray.plan.x * cameraX, ray.direction.y + ray.plan.y * cameraX};
		map = (t_resolution) {(short)runtime->player.position.x, (short)runtime->player.position.y};
		side = (t_position) {direction.x < 0 ? runtime->player.position.x - map.width : map.width + 1.0 - runtime->player.position.x, direction.y < 0 ? runtime->player.position.y - map.height : map.height + 1.0 - runtime->player.position.y};
		
		side.x *= fabs(1 / direction.x);
		side.y *= fabs(1 / direction.y);

		while (1)
		{
			if (side.x < side.y)
				map.width += direction.x < 0 ? -1 : 1;
			else
				map.height += direction.y < 0 ? -1 : 1;
			if (runtime->file.map[map.height][map.width] == '1')
				break;
			if (side.x < side.y)
				side.x += fabs(1 / direction.x);
			else
				side.y += fabs(1 / direction.y);
		}

		if (side.x < side.y)
			lineHeight = runtime->file.resolution.height * direction.x / (map.width - runtime->player.position.x + (1 - (direction.x < 0 ? -1 : 1)) / 2);
		else
			lineHeight = runtime->file.resolution.height * direction.y / (map.height - runtime->player.position.y + (1 - (direction.y < 0 ? -1 : 1)) / 2);

		draw = (t_resolution) {-lineHeight / 2 + runtime->file.resolution.height / 2, 0};
		if ((short)draw.width < 0)
			draw.width = 0;
		draw.height = lineHeight / 2 + runtime->file.resolution.height / 2;
		if (draw.height >= runtime->file.resolution.height)
			draw.height = runtime->file.resolution.height - 1;

		if (side.x < side.y)
			cameraX = runtime->player.position.y + (map.width - runtime->player.position.x + (1 - (direction.x < 0 ? -1 : 1)) / 2) / direction.x * direction.y;
		else
			cameraX = runtime->player.position.x + (map.height - runtime->player.position.y + (1 - (direction.y < 0 ? -1 : 1)) / 2) / direction.y * direction.x;
		cameraX -= floor((cameraX));

		map = (t_resolution) {(cameraX * (double)(runtime->file.north.resolution.width)), 0};

		/// a modifier
		if ((side.x < side.y && direction.x < 0) || (side.x > side.y && direction.y > 0))
			map.width = runtime->file.north.resolution.width - map.width - 1;
		///

		direction.y = 1.0 * runtime->file.north.resolution.height / lineHeight;
		direction.x = (draw.width - runtime->file.resolution.height / 2 + lineHeight / 2) * direction.y;
		for (int y = draw.width; y < draw.height; y++)
		{
			map.height = (int)direction.x & (runtime->file.north.resolution.height - 1);
			direction.x += direction.y;
			int color = runtime->file.north.data[runtime->file.north.resolution.width * map.height + map.width];
			runtime->mlx.data[runtime->file.resolution.width * y + x] = color;
		}
		x++;
	}
}

int		update_image(t_runtime *runtime)
{
	static bool		editing;
	static clock_t	last_frame;
	t_ray			ray;

	if (runtime->player.updated || editing)
		return (1);
	if (last_frame && 1000000 / MAX_FPS > clock() - last_frame)
		return (2);
	editing = true;
	last_frame = clock();
	runtime->mlx.image = mlx_new_image(runtime->mlx.mlx, runtime->file.resolution.width, runtime->file.resolution.height);
	runtime->mlx.data = image_data(runtime->mlx.image, runtime->file.resolution.width);

	ray = (t_ray){{sin(runtime->player.degree * M_PI / 180), -1 * cos(runtime->player.degree * M_PI / 180)}, {cos(runtime->player.degree * M_PI / 180) * FOV / 100, sin(runtime->player.degree * M_PI / 180) * FOV / 100}};

	update_floor(runtime, ray);
	update_wall(runtime, ray);

	mlx_put_image_to_window(runtime->mlx.mlx, runtime->mlx.window, runtime->mlx.image, 0, 0);
	runtime->player.updated = true;
	editing = false;
	update_keys(runtime);
	if (runtime->save)
	{
		bitmap("save.bmp", runtime);
		runtime->save = false;
	}
	mlx_destroy_image(runtime->mlx.mlx, runtime->mlx.image);
	if (runtime->end)
		end(runtime);
	return (0);
}