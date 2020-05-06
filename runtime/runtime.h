/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:17:23 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/06 23:39:23 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# ifndef FOV
#  define FOV 70
# endif

# ifndef FORWARD
#  define FORWARD 119
# endif

# ifndef BACKWARD
#  define BACKWARD 115
# endif

# ifndef LEFT
#  define LEFT 97
# endif

# ifndef RIGHT
#  define RIGHT 100
# endif

# include "../main/cub3d.h"
# include <mlx.h>

typedef struct	s_position
{
	float	x;
	float	y;
}				t_position;

typedef struct	s_player
{
	float		degree;
	t_position	position;
	bool		initiate;
}				t_player;

typedef struct	s_mlx
{
	t_settings	settings;
	t_player	player;
	void		*mlx;
	void		*win;
	void		*img;
}				t_mlx;

typedef struct	s_ajust
{
	t_position	position;
	t_position	direction;
	t_position	plan;
}				t_ajust;

typedef struct	s_ray
{
	t_position	position;
	t_position	direction;
	t_position	side;
	t_position	delta;
	t_position	step;
}				t_ray;

void			ft_detect(t_mlx *mlx);
int				ft_update(t_mlx *mlx);
t_ajust			ft_ajust(t_player player);
float			ft_distance(float cameraX, t_ajust ajust, char **map);

#endif
