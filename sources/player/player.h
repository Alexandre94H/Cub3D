#ifndef		PLAYER_H
# define	PLAYER_H

#include <stdbool.h>
#include "../file/file.h"

typedef struct	s_sprite
{
	t_position		position;
	unsigned char	index;
}				t_sprite;

typedef struct	s_player
{
	float	degree;
	t_position		position;
	t_sprite		**sprites;
	bool			updated;
}				t_player;

int		init_player(char **map, t_player *player);

#endif