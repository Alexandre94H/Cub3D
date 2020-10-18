/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:16:11 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/18 23:26:58 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_full.h"

void	sprite_color(t_runtime *runtime, t_resolution position,
	t_texture texture, t_resolution texture_position)
{
	int	color;

	color = texture.data[texture.resolution.width
		* texture_position.height + texture_position.width];
	if (color)
		runtime->mlx.data[runtime->file.resolution.width
			* position.height + position.width] = color;
}

void	sprite_loop_y(t_runtime *runtime, t_sprite_variable sprite,
	t_resolution y_max, unsigned short x)
{
	unsigned short	y;
	unsigned short	texture_x;

	texture_x = (x - (-sprite.sprite.width / 2 + (short)(runtime->file.
		resolution.width / 2 * (1 + sprite.transform.x / sprite.
		transform.y)))) * sprite.texture.resolution.width
		/ sprite.sprite.width;
	y = y_max.width;
	while (y < y_max.height)
	{
		sprite_color(runtime, (t_resolution){x, y}, sprite.texture,
		(t_resolution){texture_x, (y - runtime->player.pitch * 200 -
		runtime->player.position.z * 200 / sprite.transform.y + (sprite.
		sprite.height - runtime->file.resolution.height) / 2) * sprite.
		texture.resolution.height / sprite.sprite.height});
		y++;
	}
}

void	sprite_loop_x(t_runtime *runtime, t_sprite_variable sprite,
	t_resolution x_max, t_resolution y_max)
{
	unsigned short	x;

	x = x_max.width;
	while (x < x_max.height)
	{
		if (sprite.transform.y > 0 && x > 0 && x < runtime->file.
			resolution.width && sprite.transform.y < runtime->mlx.buffer[x])
			sprite_loop_y(runtime, sprite, y_max, x);
		x++;
	}
}
