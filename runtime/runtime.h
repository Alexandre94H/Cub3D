/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:17:23 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/20 18:36:32 by ahallain         ###   ########.fr       */
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

# ifndef CAMERA_UP
#  define CAMERA_UP 65362
# endif

# ifndef CAMERA_DOWN
#  define CAMERA_DOWN 65364
# endif

# ifndef FPS
#  define FPS 24
# endif

# ifndef TEXTURE_SIDE
#  define TEXTURE_SIDE 64
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
	bool		initiate;
	float		degree;
	t_position	position;
	float		camera;
}				t_player;

typedef struct	s_input
{
	bool	forward;
	bool	backward;
	bool	turn_left;
	bool	turn_right;
	bool	rotate_left;
	bool	rotate_right;
	bool	camera_up;
	bool	camera_down;
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

typedef struct	s_wall
{
	int		length;
	size_t	y;
	size_t	last;
	float	texture_y;
}				t_wall;

typedef struct	s_floor
{
	float	distance;
	float	floorx;
	float	floory;
	float	stepx;
	float	stepy;
}				t_floor;

typedef struct	s_ray
{
	t_position	direction;
	t_position	plane;
	float		degree;
}				t_ray;

typedef struct	s_calc
{
	float	distance;
	float	texture_x;
	int		side;
}				t_calc;

t_mlx			ft_init_mlx(char *title, t_settings settings, t_player player);
void			ft_detect(t_mlx *mlx);
int				ft_update(t_mlx *mlx);
int				ft_run(char *title, t_settings settings);
void			ft_bitmap(t_mlx *mlx);
int				ft_destroy(t_mlx *mlx);
bool			ft_check_input(t_mlx mlx);
void			ft_update_input(t_mlx *mlx, t_position direction);
int				ft_fade(int color, float divide);
void			ft_set_floor(t_mlx *mlx, t_ray ray);
void			ft_set_wall(t_mlx *mlx, t_ray ray);
void			ft_set_skybox(t_mlx *mlx);
int				*ft_data(void *img_ptr, int size_line);
int				ft_get_color(t_xpm xpm, size_t index);
int				ft_destroy(t_mlx *mlx);
void			ft_music(char *path);
void			ft_music_clear();

#endif
