/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:32:54 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/18 22:18:12 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../mlx_full.h"

bool			dda(t_runtime *runtime, t_position ray_direction,
	t_resolution *position)
{
	t_position	side;
	t_position	step;

	*position = (t_resolution){runtime->player.position.x,
		runtime->player.position.y};
	side = (t_position){(position->width + (ray_direction.x >= 0)
		- runtime->player.position.x) / ray_direction.x, (position->height +
		(ray_direction.y >= 0) - runtime->player.position.y) / ray_direction.y};
	step = (t_position){(ray_direction.x > 0) * 2 - 1,
		(ray_direction.y > 0) * 2 - 1};
	while (1)
	{
		if (side.x < side.y)
			position->width += step.x;
		else
			position->height += step.y;
		if (runtime->file.map[position->height][position->width] == '1')
			break ;
		if (side.x < side.y)
			side.x += step.x / ray_direction.x;
		else
			side.y += step.y / ray_direction.y;
	}
	return (side.x < side.y);
}

unsigned short	wall_texture(t_runtime *runtime, t_resolution x_side,
	t_position ray_direction, t_texture *texture)
{
	unsigned short	texture_x;

	if (x_side.height)
		if (ray_direction.x < 0)
			*texture = runtime->file.west;
		else
			*texture = runtime->file.east;
	else if (ray_direction.y < 0)
		*texture = runtime->file.north;
	else
		*texture = runtime->file.south;
	if (x_side.height)
		texture_x = (runtime->player.position.y + runtime->mlx.
			buffer[x_side.width] * ray_direction.y) * texture->resolution.width;
	else
		texture_x = (runtime->player.position.x + runtime->mlx.
		buffer[x_side.width] * ray_direction.x) * texture->resolution.width;
	texture_x -= texture->resolution.width
		* (unsigned short)(texture_x / texture->resolution.width);
	if (x_side.height && ray_direction.x < 0)
		texture_x = texture->resolution.width - texture_x - 1;
	if (!x_side.height && ray_direction.y > 0)
		texture_x = texture->resolution.width - texture_x - 1;
	return (texture_x);
}

unsigned short	wall_y(t_runtime runtime, unsigned short x, unsigned short *y)
{
	int				y1;
	unsigned short	y_max;

	y1 = runtime.file.resolution.height / 2 * (1 - 1 / runtime.mlx.buffer[x])
		+ runtime.player.pitch * 200 + (runtime.player.position.z * 200
		/ runtime.mlx.buffer[x]);
	if (y1 < 0)
		y1 = 0;
	*y = y1;
	y_max = runtime.file.resolution.height / 2 * (1 + 1 / runtime.mlx.buffer[x])
		+ runtime.player.pitch * 200 + (runtime.player.position.z * 200
		/ runtime.mlx.buffer[x]);
	if (y_max >= runtime.file.resolution.height)
		y_max = runtime.file.resolution.height - 1;
	return (y_max);
}

void			wall_loop(t_runtime *runtime, unsigned short x,
	t_texture texture, unsigned short texture_x)
{
	unsigned short	y;
	unsigned short	y_max;
	float			texture_y;
	float			step;
	int				color;

	y_max = wall_y(*runtime, x, &y);
	step = runtime->mlx.buffer[x] * texture.resolution.height /
		runtime->file.resolution.height;
	texture_y = y - runtime->player.pitch * 200 - (runtime->player.position.z
		* 200 / runtime->mlx.buffer[x]) - runtime->file.resolution.height / 2
		+ runtime->file.resolution.height / runtime->mlx.buffer[x] / 2;
	texture_y = texture_y < 0 ? 0 : texture_y * step;
	while (y < y_max)
	{
		color = texture.data[texture.resolution.height *
			(unsigned short)texture_y + texture_x];
		runtime->mlx.data[y * runtime->file.resolution.width + x] = color;
		texture_y += step;
		y++;
	}
}

void			update_wall(t_runtime *runtime, t_ray ray)
{
	unsigned short	x;
	t_position		ray_direction;
	t_resolution	position;
	bool			side;
	t_texture		texture;

	x = 0;
	while (x < runtime->file.resolution.width)
	{
		ray_direction = (t_position){ray.direction.x + ray.plan.x *
			(2 * x / (double)(runtime->file.resolution.width) - 1),
			ray.direction.y + ray.plan.y * (2 * x /
			(double)(runtime->file.resolution.width) - 1)};
		side = dda(runtime, ray_direction, &position);
		if (side)
			runtime->mlx.buffer[x] = (position.width - runtime->
				player.position.x + (ray_direction.x < 0)) / ray_direction.x;
		else
			runtime->mlx.buffer[x] = (position.height - runtime->
				player.position.y + (ray_direction.y < 0)) / ray_direction.y;
		wall_loop(runtime, x, texture, wall_texture(runtime,
			(t_resolution){x, side}, ray_direction, &texture));
		x++;
	}
}
