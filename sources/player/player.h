#ifndef		PLAYER_H
# define	PLAYER_H

#include <stdbool.h>
#include "../file/file.h"

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

int		init_player(char **map, t_player *player);

#endif