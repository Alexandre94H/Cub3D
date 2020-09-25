#ifndef		MLX1_H
# define	MLX1_H

#include "../file/file.h"
#include "../player/player.h"

typedef struct	s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
	void	*data;
}				t_mlx;

typedef struct	s_runtime
{
	t_file		file;
	t_player	player;
	t_mlx		mlx;
}				t_runtime;

void	init_mlx(t_file *file, t_mlx *mlx);
void	loop(char *name, t_runtime runtime);
#endif