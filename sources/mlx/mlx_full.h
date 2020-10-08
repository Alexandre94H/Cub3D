#ifndef		MLX_FULL_H
# define	MLX_FULL_H

#include "mlx1.h"

#define		TEXTURE_SIDE 64
#define		FOV 70

typedef struct	s_ray {
	t_position	direction;
	t_position	plan;
}				t_ray;

int				update_image(t_runtime *runtime);
unsigned int	*image_data(void *image, unsigned short width);
int				press(int key, t_runtime *runtime);
int				release(int key, t_runtime *runtime);
void			update_keys(t_runtime *runtime);
void			bitmap(char *filename, t_runtime *runtime);
void			end(t_runtime *runtime);

#endif