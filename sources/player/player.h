/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:36:06 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/19 20:41:06 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdbool.h>
# include "../file/file.h"

typedef struct	s_position
{
	float	x;
	float	y;
}				t_position;

typedef struct	s_position_3d
{
	float	x;
	float	y;
	float	z;
}				t_position_3d;

typedef struct	s_sprite
{
	t_position		position;
	unsigned char	index;
}				t_sprite;

typedef struct	s_player
{
	float			degree;
	t_position_3d	position;
	float			pitch;
	t_sprite		**sprites;
	bool			updated;
}				t_player;

unsigned char	init_player(char **map, t_player *player);
#endif
