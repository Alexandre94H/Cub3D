/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:33:06 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 18:54:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_full.h"

void			sprite_sort(t_runtime *runtime)
{
	unsigned short	length;
	float			last_distance;
	float			current_distance;
	t_sprite		*sprite;

	length = 0;
	while ((sprite = runtime->player.sprites[length]))
	{
		last_distance = current_distance;
		current_distance = (runtime->player.position.x - sprite->position.x)
			* (runtime->player.position.x - sprite->position.x)
			+ (runtime->player.position.y - sprite->position.y)
			* (runtime->player.position.y - sprite->position.y);
		if (length && last_distance < current_distance)
		{
			runtime->player.sprites[length] = runtime->
				player.sprites[length - 1];
			runtime->player.sprites[length - 1] = sprite;
		}
		length++;
	}
}

t_resolution	sprite_x(t_runtime runtime, t_position transform,
	t_texture texture, t_resolution *x_max)
{
	t_position		division;
	t_resolution	sprite;
	int				sprite_screen_x;
	int				max;

	division = (t_position){1 + (texture.resolution.width < texture.resolution
		.height) * ((float)texture.resolution.height / texture.resolution.width)
		/ 2, 1 + (texture.resolution.height < texture.resolution.width)
		* ((float)texture.resolution.width / texture.resolution.height) / 2};
	sprite = (t_resolution){runtime.file.resolution.height / transform.y /
		division.x, runtime.file.resolution.height / transform.y / division.y};
	sprite_screen_x = (runtime.file.resolution.width / 2)
		* (1 + transform.x / transform.y);
	max = -1 * sprite.width / 2 + sprite_screen_x;
	if (max < 0)
		max = 0;
	x_max->width = max;
	max = sprite.width / 2 + sprite_screen_x;
	if (max < 0)
		max = 0;
	if (max >= runtime.file.resolution.width)
		max = runtime.file.resolution.width - 1;
	x_max->height = max;
	return (sprite);
}

t_resolution	sprite_y(t_runtime runtime, t_position transform,
	t_resolution sprite)
{
	unsigned short	screen_move;
	int				max;
	t_resolution	y_max;

	screen_move = runtime.player.pitch * 200
		+ runtime.player.position.z * 200 / transform.y;
	max = -1 * sprite.height / 2
		+ runtime.file.resolution.height / 2 + screen_move;
	if (max < 0)
		max = 0;
	y_max.width = max;
	max = sprite.height / 2
		+ runtime.file.resolution.height / 2 + screen_move;
	if (max < 0)
		max = 0;
	y_max.height = max;
	if (y_max.height >= runtime.file.resolution.height)
		y_max.height = runtime.file.resolution.height - 1;
	return (y_max);
}

t_position		sprite_transform(t_runtime runtime, t_ray ray, t_sprite sprite)
{
	return ((t_position){(ray.direction.y * (sprite.position.x - runtime.
		player.position.x) - ray.direction.x * (sprite.position.y -
		runtime.player.position.y)) / (ray.plan.x * ray.direction.y -
		ray.direction.x * ray.plan.y), (-ray.plan.y * (sprite.position.x -
		runtime.player.position.x) + ray.plan.x * (sprite.position.y -
		runtime.player.position.y)) / (ray.plan.x * ray.direction.y -
		ray.direction.x * ray.plan.y)});
}

void			update_sprite(t_runtime *runtime, t_ray ray)
{
	unsigned short		length;
	t_sprite_variable	sprite;
	t_resolution		x_max;

	if (!runtime->player.sprites)
		return ;
	sprite_sort(runtime);
	length = 0;
	while (runtime->player.sprites[length])
	{
		sprite.texture = *runtime->file.sprites[
			runtime->player.sprites[length]->index];
		sprite.transform = sprite_transform(*runtime, ray,
			*runtime->player.sprites[length]);
		sprite.sprite = sprite_x(*runtime, sprite.transform, sprite.texture,
			&x_max);
		sprite_loop_x(runtime, sprite, x_max, sprite_y(*runtime,
			sprite.transform, sprite.sprite));
		length++;
	}
}
