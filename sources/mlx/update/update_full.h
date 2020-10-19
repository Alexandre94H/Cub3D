/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_full.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:32:58 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/19 09:50:15 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_FULL_H
# define UPDATE_FULL_H

# include "../mlx_full.h"

typedef struct	s_sprite_variable
{
	t_texture		texture;
	t_position		transform;
	t_resolution	sprite;
}				t_sprite_variable;

void	sprite_color(t_runtime *runtime, t_resolution position,
	t_texture texture, t_resolution texture_position);
void	sprite_loop_y(t_runtime *runtime, t_sprite_variable sprite,
	t_resolution y_max, unsigned short x);
void	sprite_loop_x(t_runtime *runtime, t_sprite_variable sprite,
	t_resolution x_max, t_resolution y_max);
#endif
