#ifndef		MLX1_H
# define	MLX1_H

#include <stdbool.h>
#include "../file/file.h"
#include "../player/player.h"

#define		MAX_FPS 60

typedef struct	s_mlx
{
	void			*mlx;
	void			*window;
	void			*image;
	unsigned int	*data;

}				t_mlx;

typedef struct s_runtime t_runtime;
typedef	void  (*key)(t_runtime *);

struct	s_runtime
{
	t_file		file;
	t_player	player;
	t_mlx		mlx;
	key			*keys;
	bool		save;
	bool		end;
};

void	init_mlx(t_file *file, t_mlx *mlx, t_player *player);
void	loop(char *name, t_runtime runtime);
#endif
