#ifndef		PLAYER_H
# define	PLAYER_H

#include "../file/file.h"

typedef struct	s_player
{
	unsigned char	angle;
	t_resolution	resolution;
}				t_player;

int		init_player(unsigned char **map, t_player *player);

#endif