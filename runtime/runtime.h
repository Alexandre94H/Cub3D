/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:17:23 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/18 20:02:41 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# ifndef FORWARD
#  define FORWARD 119
# endif

# ifndef BACKWARD
#  define BACKWARD 115
# endif

# ifndef TURN_LEFT
#  define TURN_LEFT 97
# endif

# ifndef TURN_RIGHT
#  define TURN_RIGHT 100
# endif

# ifndef FPS
#  define FPS 60
# endif

# include <stdbool.h>
# include <stddef.h>
# include "../parse/parse.h"

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

typedef struct	s_input
{
	bool	forward;
	bool	backward;
	bool	turn_left;
	bool	turn_right;
	bool	rotate_left;
	bool	rotate_right;
}				t_input;

typedef struct	s_mlx
{
	t_settings	settings;
	t_player	player;
	t_input		input;
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
}				t_mlx;

typedef struct	s_loop
{
	int		length;
	size_t	first;
	size_t	last;
	float	texture_y;
	size_t	y;
	int		filter;
}				t_loop;

t_mlx			ft_init_mlx(char *title, t_settings settings, t_player player);
void			ft_detect(t_mlx *mlx);
int				ft_update(t_mlx *mlx);
int				ft_run(char *title, t_settings settings);
void			ft_bitmap(t_mlx mlx, char *filename);
int				ft_destroy(t_mlx *mlx);

#endif
